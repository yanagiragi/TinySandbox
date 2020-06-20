#include "CubemapConverter.hpp"

#include "Cube.hpp"
#include "SkyboxMaterial.hpp"
#include "EquirectangularToCubemapMaterial.hpp"
#include "CubemapConvolveMaterial.hpp"
#include "CubemapPrefilterMaterial.hpp"

#include "Windows.hpp"

TinySandbox::CubemapConverter* TinySandbox::CubemapConverter::m_instance = nullptr;

namespace TinySandbox
{
	CubemapConverter::CubemapConverter()
	{
		this->SetMesh(new Cube());
		m_frameBufferObject = TEXTURE_NOT_INITIALIZED; // magic number to mean "un-initialized"
		m_renderBufferObject= TEXTURE_NOT_INITIALIZED;

		// leave _renderer as nullptr since it is a lazy update
		m_convertMaterial = new EquirectangularToCubemapMaterial();
		m_convoluteMaterial = new CubemapConvolveMaterial();
		m_prefilterMaterial = new CubemapPrefilterMaterial();
	}

	CubemapConverter::~CubemapConverter()
	{
		m_frameBufferObject = TEXTURE_NOT_INITIALIZED;
		m_renderBufferObject = TEXTURE_NOT_INITIALIZED;
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

		if (CubemapConverter::Instance()->m_frameBufferObject == TEXTURE_NOT_INITIALIZED || CubemapConverter::Instance()->m_renderBufferObject == TEXTURE_NOT_INITIALIZED) {
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
			#ifdef WIN32
				channelType = GraphicsAPI_DataType::RGB16F;
				formatType = GraphicsAPI_DataType::FLOAT;
			#else
				// behaves wierd in linux platform, fallback to LDR instead
				channelType = GraphicsAPI_DataType::RGB;
				formatType = GraphicsAPI_DataType::UNSIGNED_BYTE;
			#endif
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

			_material->SetIndex(i);
			_material->Use();

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
		CubemapConverter::Instance()->m_convertMaterial->SetMainTexture(&_tex);
		CubemapConverter::BiltCubemap(cubemapId, CubemapConverter::Instance()->m_convertMaterial, cubemapResolution);

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
		CubemapConverter::Instance()->m_convoluteMaterial->SetMainTexture(&_tex);

		CubemapConverter::BiltCubemap(cubemapId, CubemapConverter::Instance()->m_convoluteMaterial, cubemapResolution);

		return cubemapId;
	}

	unsigned int CubemapConverter::ConvertCubemapToPrefilteredCubemap(Texture& _tex)
	{
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();
		unsigned int cubemapResolution = _tex.m_prefiltercubemapResolution;
		unsigned int maxMipLevels = _tex.m_mipsLevel;
		unsigned int cubemapId;

		// 1. Setup FrameBuffer
		CubemapConverter::SetupFrameBufferAndRenderBuffer(cubemapResolution);

		// 2. Initialize Texture
		CubemapConverter::SetupCubemapTexture(cubemapId, cubemapResolution, _tex.isHighDynamicRange);

		m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, cubemapId);
		
		// override setting from CubemapConverter::SetupCubemapTexture()
		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, GraphicsAPI_DataType::TEXTURE_MIN_FILTER, GraphicsAPI_DataType::LINEAR_MIPMAP_LINEAR);
		m_api->GenerateMipmap(GraphicsAPI_DataType::TEXTURE_CUBE_MAP);
		m_api->UnbindTexture(GraphicsAPI_DataType::TEXTURE_CUBE_MAP); // remember to clean up
		
		// 3. Bilt PrefilterMaterial with Lod Settings

		// setup input texture conversion material to source texture
		CubemapConverter::Instance()->m_prefilterMaterial->SetMainTexture(&_tex);

		m_api->BindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, CubemapConverter::Instance()->m_frameBufferObject);
		CubemapConverter::Instance()->m_prefilterMaterial->SetMaxLod(maxMipLevels);

		for (unsigned int mip = 0; mip < maxMipLevels; ++mip) {

			GraphicsAPI_DataType targetType = GraphicsAPI_DataType::LEN;
			for (int i = 0; i < 6; ++i)
			{
				unsigned int mipWidth = cubemapResolution * std::pow(0.5, mip);
				unsigned int mipHeight = cubemapResolution * std::pow(0.5, mip);

				m_api->BindRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, CubemapConverter::Instance()->m_renderBufferObject);
				m_api->SetRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, GraphicsAPI_DataType::DEPTH_COMPONENT24, mipWidth, mipHeight);
				m_api->SetViewport(0, 0, mipWidth, mipHeight);

				CubemapConverter::Instance()->m_prefilterMaterial->SetIndex(i);
				CubemapConverter::Instance()->m_prefilterMaterial->SetLod(mip);

				CubemapConverter::Instance()->m_prefilterMaterial->Use();

				switch (i) {
				case 0: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_X; break;
				case 1: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_X; break;
				case 2: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Y; break;
				case 3: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Y; break;
				case 4: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Z; break;
				case 5: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Z; break;
				default: throw "undefined targetType"; break;
				}

				m_api->SetFrameBuffer2D(GraphicsAPI_DataType::FRAMEBUFFER, GraphicsAPI_DataType::COLOR_ATTACHMENT0, targetType, cubemapId, mip);

				m_api->ClearScreenColor();
				m_api->ClearScreenDepth();

				m_api->BindVertexArray(CubemapConverter::Instance()->m_VAO);
				m_api->DrawArrays(GraphicsAPI_DataType::TRIANGLES, CubemapConverter::Instance()->m_mesh->vertex.size());
			}

		}

		// Clean up
		CubemapConverter::Instance()->m_prefilterMaterial->Unuse();
		m_api->UnbindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER);
		m_api->UnbindVertexArray();
		m_api->UnbindProgram();

		Windows* window = Windows::GetInstance();
		m_api->SetViewport(0, 0, window->GetWidth(), window->GetHeight());

		return cubemapId;
	}

	void CubemapConverter::ConvertToCubemapAndFilter(Texture& _tex)
	{
		_tex.m_textureId = CubemapConverter::ConvertEquirectangularToCubemap(_tex);

		_tex.m_convTextureId = CubemapConverter::ConvertCubemapToConvolutedCubemap(_tex);

		_tex.m_prefilterTextureId = CubemapConverter::ConvertCubemapToPrefilteredCubemap(_tex);
	}


	void CubemapConverter::InitializeFrameBufferObjects(GraphicsAPI* m_api)
	{
		m_api->GenerateFrameBuffers(&m_frameBufferObject, 1);
		m_api->GenerateRenderBuffers(&m_renderBufferObject, 1);
	}
}