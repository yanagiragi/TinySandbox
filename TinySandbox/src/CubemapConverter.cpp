#include "CubemapConverter.hpp"

#include "Cube.hpp"
#include "SkyboxMaterial.hpp"
#include "EquirectangularToCubemapMaterial.hpp"

#include <glmathematics/glm.hpp>
#include <glmathematics/gtc/matrix_transform.hpp>

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
		m_frameBufferObject = 4294967294;
		m_renderBufferObject= 4294967294;

		m_ConvertMaterial = new EquirectangularToCubemapMaterial(nullptr);
	}

	CubemapConverter* CubemapConverter::Instance()
	{
		if (CubemapConverter::m_instance == nullptr) {
			m_instance = new CubemapConverter();
		}
		return m_instance;
	}

	GLuint CubemapConverter::ConvertEquirectangularToCubemap(Texture& _tex)
	{
		// pbr: setup cubemap to render to and attach to framebuffer
		// ---------------------------------------------------------

		CubemapConverter::Instance()->InitializeFrameBufferObjects(GraphicsAPI::GetAPI());

		GLuint captureFBO = CubemapConverter::Instance()->m_frameBufferObject;
		GLuint captureRBO = CubemapConverter::Instance()->m_renderBufferObject;
		int envCubemapResolution = 512;
		GLuint envCubemapID;

		glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
		glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, envCubemapResolution, envCubemapResolution);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

		glGenTextures(1, &envCubemapID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemapID);
		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, envCubemapResolution, envCubemapResolution, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLuint program = GraphicsAPI::GetAPI()->CompileShader("../Shaders/EquirectangularToCubemap.vert", "", "../Shaders/EquirectangularToCubemap.frag");

		// Start Equirectangular To Cubemap Conversion
		glUseProgram(program);

		GLint projectionLocation = glGetUniformLocation(program, "u_projectionMatrix");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &captureProjection[0][0]);

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _tex.GetID());
		// GLint equirectangularMapLocation = glGetUniformLocation(program, "u_equirectangularMap");
		// glUniform1d(equirectangularMapLocation, 0);

		glViewport(0, 0, envCubemapResolution, envCubemapResolution); // don't forget to configure the viewport to the capture dimensions.
		glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
		for (unsigned int i = 0; i < 6; ++i)
		{
			GLint viewLocation = glGetUniformLocation(program, "u_viewMatrix");
			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &captureViews[i][0][0]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemapID, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_api->BindVertexArray(CubemapConverter::Instance()->m_VAO);
			m_api->DrawArrays(GraphicsAPI_DataType::TRIANGLES, CubemapConverter::Instance()->m_mesh->vertex.size());
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0, 0, 800, 600); // don't forget to configure the viewport to the capture dimensions.

		return envCubemapID;
	}

	unsigned int CubemapConverter::Convert(Texture& _tex)
	{
		return CubemapConverter::Instance()->ConvertEquirectangularToCubemap(_tex);
	}

	/*unsigned int CubemapConverter::Convert(Texture& _tex)
	{
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();

		unsigned int _cubemapResolution = _tex.GetCubemapResolution();

		// Setup FBO & RBO
		if (CubemapConverter::Instance()->m_frameBufferObject == 4294967294 || CubemapConverter::Instance()->m_renderBufferObject == 4294967294) {
			CubemapConverter::Instance()->InitializeFrameBufferObjects(m_api);
		}

		m_api->BindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, CubemapConverter::Instance()->m_frameBufferObject);
		m_api->BindRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, CubemapConverter::Instance()->m_renderBufferObject);

		m_api->SetRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, GraphicsAPI_DataType::DEPTH_COMPONENT24, _cubemapResolution, _cubemapResolution);
		m_api->AttachRenderBufferToFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, GraphicsAPI_DataType::DEPTH_ATTACHMENT, GraphicsAPI_DataType::RENDERBUFFER, CubemapConverter::Instance()->m_renderBufferObject);

		m_api->UnbindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER);

		// Setup cubeMap Texture
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

		// glViewport(0, 0, 512, 512);

		m_api->BindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, CubemapConverter::Instance()->m_frameBufferObject);
		
		CubemapConverter::Instance()->m_ConvertMaterial->SetMainTexture(&_tex);

		// Start Equirectangular To Cubemap Conversion
		for (int i = 0; i < 6; ++i)
		{
			CubemapConverter::Instance()->m_ConvertMaterial->Use(i);

			switch (i) {
				case 0: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_X; break;
				case 1: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_X; break;
				case 2: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Y; break;
				case 3: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Y; break;
				case 4: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Z; break;
				case 5: targetType = GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Z; break;
				default: throw "undefined targetType"; break;
			}

			m_api->SetFrameBuffer2D(GraphicsAPI_DataType::FRAMEBUFFER, GraphicsAPI_DataType::COLOR_ATTACHMENT0, targetType, cubemapID, 0);
			
			m_api->ClearScreenColor();
			m_api->ClearScreenDepth();
			
			m_api->BindVertexArray(CubemapConverter::Instance()->m_VAO);
			m_api->DrawArrays(GraphicsAPI_DataType::TRIANGLES, CubemapConverter::Instance()->m_mesh->vertex.size());
		}
		
		// Clean up
		CubemapConverter::Instance()->m_ConvertMaterial->Unuse();
		m_api->UnbindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER);
		m_api->UnbindVertexArray();
		m_api->UnbindProgram();

		return cubemapID;
	}*/


	void CubemapConverter::InitializeFrameBufferObjects(GraphicsAPI* m_api)
	{
		m_api->GenerateFrameBuffers(&m_frameBufferObject, 1);
		m_api->GenerateRenderBuffers(&m_renderBufferObject, 1);
	}
}