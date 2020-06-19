#include "CubemapConverter.hpp"

#include "Cube.hpp"
#include "SkyboxMaterial.hpp"
#include "EquirectangularToCubemapMaterial.hpp"

#include "Windows.hpp"

TinySandbox::CubemapConverter* TinySandbox::CubemapConverter::m_instance = nullptr;
const glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
const glm::mat4 captureViews[] = {
	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
};

namespace TinySandbox
{
	CubemapConverter::CubemapConverter()
	{
		this->SetMesh(new Cube());
		m_frameBufferObject = 4294967294; // magic number to mean "un-initialized"
		m_renderBufferObject= 4294967294;

		// leave _renderer as nullptr since it is a lazy update
		m_ConvertMaterial = new EquirectangularToCubemapMaterial(nullptr);
		m_ConvoluteMaterial = new CubemapIrradianceConvolutionMaterial(nullptr);
	}

	CubemapConverter::~CubemapConverter()
	{
		m_frameBufferObject = 4294967294;
		m_renderBufferObject = 4294967294;
	}

	CubemapConverter* CubemapConverter::Instance()
	{
		if (CubemapConverter::m_instance == nullptr) {
			m_instance = new CubemapConverter();
		}
		return m_instance;
	}

	void CubemapConverter::SetupFrameBufferAndRenderBuffer(unsigned int _resolution) {
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();

		if (CubemapConverter::Instance()->m_frameBufferObject == 4294967294 || CubemapConverter::Instance()->m_renderBufferObject == 4294967294) {
			CubemapConverter::Instance()->InitializeFrameBufferObjects(m_api);

			m_api->BindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, CubemapConverter::Instance()->m_frameBufferObject);
			m_api->BindRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, CubemapConverter::Instance()->m_renderBufferObject);

			m_api->SetRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, GraphicsAPI_DataType::DEPTH_COMPONENT24, _resolution, _resolution);
			m_api->AttachRenderBufferToFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, GraphicsAPI_DataType::DEPTH_ATTACHMENT, GraphicsAPI_DataType::RENDERBUFFER, CubemapConverter::Instance()->m_renderBufferObject);

			m_api->UnbindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER);
		}		
	};

	void CubemapConverter::SetupCubemapTexture(unsigned int& _target, unsigned int _resolution, bool isHDR) {

		GraphicsAPI* m_api = GraphicsAPI::GetAPI();
		unsigned int cubemapID;

		m_api->GenerateTextures(&cubemapID, 1);
		m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, cubemapID);

		GraphicsAPI_DataType channelType;
		GraphicsAPI_DataType formatType;

		if (isHDR) {
			channelType = GraphicsAPI_DataType::RGB16F;
			formatType = GraphicsAPI_DataType::FLOAT;
		}
		else {
			channelType = GraphicsAPI_DataType::RGB;
			formatType = GraphicsAPI_DataType::UNSIGNED_BYTE;
		}

		GraphicsAPI_DataType targetType = GraphicsAPI_DataType::LEN;
		for (int i = 0; i < 6; ++i) {

			switch (i) {
			case 0: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_X; break;
			case 1: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_X; break;
			case 2: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Y; break;
			case 3: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Y; break;
			case 4: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Z; break;
			case 5: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Z; break;
			default: throw "undefined targetType"; break;
			}

			m_api->SetTexture2D(
				targetType,
				0, // lod level = 0
				channelType,
				_resolution,
				_resolution,
				0, // border,
				GraphicsAPI_DataType::RGB,
				formatType,
				nullptr
			);
		}

		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, GraphicsAPI_DataType::TEXTURE_WRAP_S, GraphicsAPI_DataType::CLAMP_TO_EDGE);
		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, GraphicsAPI_DataType::TEXTURE_WRAP_T, GraphicsAPI_DataType::CLAMP_TO_EDGE);
		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, GraphicsAPI_DataType::TEXTURE_WRAP_R, GraphicsAPI_DataType::CLAMP_TO_EDGE);

		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, GraphicsAPI_DataType::TEXTURE_MIN_FILTER, GraphicsAPI_DataType::LINEAR);
		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, GraphicsAPI_DataType::TEXTURE_MAG_FILTER, GraphicsAPI_DataType::LINEAR);

		m_api->UnbindTexture(GraphicsAPI_DataType::TEXTURE_CUBE_MAP);

		// set result to _target
		_target = cubemapID;
	};
	
	void CubemapConverter::BiltCubemap(unsigned int _targetTextureId, Cubemap_BaseMaterial* _material, unsigned int _resolution)
	{
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();

		m_api->BindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, CubemapConverter::Instance()->m_frameBufferObject);
		m_api->SetViewport(0, 0, _resolution, _resolution);

		GraphicsAPI_DataType targetType = GraphicsAPI_DataType::LEN;
		for (int i = 0; i < 6; ++i) {

			_material->Use(i);

			switch (i) {
				case 0: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_X; break;
				case 1: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_X; break;
				case 2: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Y; break;
				case 3: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Y; break;
				case 4: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Z; break;
				case 5: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Z; break;
				default: throw "undefined targetType"; break;
			}

			m_api->SetFrameBuffer2D(GraphicsAPI_DataType::FRAMEBUFFER, GraphicsAPI_DataType::COLOR_ATTACHMENT0, targetType, _targetTextureId, 0);

			m_api->ClearScreenColor();
			m_api->ClearScreenDepth();

			m_api->BindVertexArray(CubemapConverter::Instance()->m_VAO);
			m_api->DrawArrays(GraphicsAPI_DataType::TRIANGLES, CubemapConverter::Instance()->m_mesh->vertex.size());
		}

		// Clean up
		_material->Unuse();
		m_api->UnbindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER);
		m_api->UnbindVertexArray();
		m_api->UnbindProgram();

		Windows* window = Windows::GetInstance();
		m_api->SetViewport(0, 0, window->GetWidth(), window->GetHeight());
	}

	unsigned int CubemapConverter::ConvertEquirectangularToCubemap(Texture& _tex)
	{
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();
		unsigned int cubemapResolution = _tex.m_cubemapResolution;
		unsigned int cubemapId;

		// 1. Setup FrameBuffer
		CubemapConverter::SetupFrameBufferAndRenderBuffer(cubemapResolution);

		// 2. Initialize Texture
		CubemapConverter::SetupCubemapTexture(cubemapId, cubemapResolution, _tex.isHighDynamicRange);

		// 3. Bilt EquirectangularConversionMaterial

		// setup input texture conversion material to source texture
		CubemapConverter::Instance()->m_ConvertMaterial->SetMainTexture(&_tex);
		CubemapConverter::BiltCubemap(cubemapId, CubemapConverter::Instance()->m_ConvertMaterial, cubemapResolution);

		return cubemapId;
	}

	unsigned int CubemapConverter::ConvertCubemapToConvolutedCubemap(Texture& _tex)
	{
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();
		unsigned int cubemapResolution = _tex.m_convCubemapResolution;
		unsigned int cubemapId;

		// 1. Setup FrameBuffer
		CubemapConverter::SetupFrameBufferAndRenderBuffer(cubemapResolution);

		// 2. Initialize Texture
		CubemapConverter::SetupCubemapTexture(cubemapId, cubemapResolution, _tex.isHighDynamicRange);

		// 3. Bilt ConvolutionMaterial
		
		// setup input texture conversion material to source texture
		CubemapConverter::Instance()->m_ConvoluteMaterial->SetMainTexture(&_tex);

		CubemapConverter::BiltCubemap(cubemapId, CubemapConverter::Instance()->m_ConvoluteMaterial, cubemapResolution);

		return cubemapId;
	}

	unsigned int CubemapConverter::ConvertCubemapToPrefilteredCubemap(Texture& _tex)
	{
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();
		unsigned int cubemapResolution = _tex.m_prefiltercubemapResolution;
		unsigned int mipsLevel = _tex.m_mipsLevel;
		unsigned int cubemapId;

		// 1. Setup FrameBuffer
		CubemapConverter::SetupFrameBufferAndRenderBuffer(cubemapResolution);

		// 2. Initialize Texture
		CubemapConverter::SetupCubemapTexture(cubemapId, cubemapResolution, _tex.isHighDynamicRange);

		// 3. Bilt PrefilterMaterial with Lod Settings

		// do something, might not able to use BiltCubemap!

		// setup input texture conversion material to source texture
		/*CubemapConverter::Instance()->m_ConvoluteMaterial->SetMainTexture(&_tex);

		CubemapConverter::BiltCubemap(cubemapId, CubemapConverter::Instance()->m_ConvoluteMaterial, _cubemapResolution);*/

		return cubemapId;
	}

	void CubemapConverter::ConvertToCubemapAndFilter(Texture& _tex)
	{
		_tex.m_textureId = CubemapConverter::ConvertEquirectangularToCubemap(_tex);

		_tex.m_convTextureId = CubemapConverter::ConvertCubemapToConvolutedCubemap(_tex);
	}


	void CubemapConverter::InitializeFrameBufferObjects(GraphicsAPI* m_api)
	{
		m_api->GenerateFrameBuffers(&m_frameBufferObject, 1);
		m_api->GenerateRenderBuffers(&m_renderBufferObject, 1);
	}
}