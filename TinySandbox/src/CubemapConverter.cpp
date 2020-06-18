#include "CubemapConverter.hpp"

#include "Cube.hpp"
#include "SkyboxMaterial.hpp"

unsigned int TinySandbox::CubemapConverter::m_frameBufferObject = 4294967294;
unsigned int TinySandbox::CubemapConverter::m_renderBufferObject = 4294967294;

namespace TinySandbox
{
	CubemapConverter::CubemapConverter()
	{

	}

	void CubemapConverter::Convert(Texture& _tex)
	{
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();

		unsigned int _cubemapResolution = _tex.GetCubemapResolution();

		// Setup Textures				
		if (m_frameBufferObject == 4294967295 || m_renderBufferObject == 4294967295) {
			CubemapConverter::InitializeFrameBufferObjects(m_api);
		}

		m_api->BindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, m_frameBufferObject);
		m_api->BindRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, m_renderBufferObject);

		m_api->SetRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, GraphicsAPI_DataType::DEPTH_COMPONENT24, _cubemapResolution, _cubemapResolution);
		m_api->AttachRenderBufferToFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, GraphicsAPI_DataType::DEPTH_ATTACHMENT, GraphicsAPI_DataType::RENDERBUFFER, m_renderBufferObject);

		unsigned int cubemapID;
		m_api->GenerateTextures(&cubemapID, 1);
		m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, cubemapID);

		GraphicsAPI_DataType channelType;
		GraphicsAPI_DataType formatType;

		if (_tex.isHighDynamicRange) {
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
				_cubemapResolution,
				_cubemapResolution,
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

		// Start Equirectangular To Cubemap Conversion
		/*program = equirectangularToCubemapProgram;
		glUseProgram(program);

		GLint equirectangularMapLocation = glGetUniformLocation(program, "equirectangularMap");
		glUniform1d(equirectangularMapLocation, 0);

		GLint projectionLocation = glGetUniformLocation(program, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &captureProjection[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, hdrTextureID);

		glViewport(0, 0, envCubemapResolution, envCubemapResolution); // don't forget to configure the viewport to the capture dimensions.
		glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
		for (unsigned int i = 0; i < 6; ++i)
		{
			GLint viewLocation = glGetUniformLocation(program, "view");
			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &captureViews[i][0][0]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemapID, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			DrawCube();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);*/
	}


	void CubemapConverter::InitializeFrameBufferObjects(GraphicsAPI* m_api)
	{
		m_api->GenerateFrameBuffers(&m_frameBufferObject, 1);
		m_api->GenerateRenderBuffers(&m_renderBufferObject, 1);
	}
}