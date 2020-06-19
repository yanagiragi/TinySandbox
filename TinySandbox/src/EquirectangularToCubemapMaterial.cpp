#include "EquirectangularToCubemapMaterial.hpp"

#include <glmathematics/glm.hpp>
#include <glmathematics/gtc/matrix_transform.hpp>

#include "CubemapConverter.hpp"

namespace TinySandbox
{
	EquirectangularToCubemapMaterial::EquirectangularToCubemapMaterial(Renderer* _renderer) : 
		Material("../Shaders/EquirectangularToCubemap.vert", "", "../Shaders/EquirectangularToCubemap.frag"),
		captureProjection( glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f) ),
		captureViews {
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
		}
	{
		m_renderer = _renderer;
		m_mainTexture = new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false);
	}

	void EquirectangularToCubemapMaterial::OnGUI()
	{

	}

	void EquirectangularToCubemapMaterial::Use(int index)
	{
		m_api->BindProgram(m_program);
		
		// Note: this is Texture2D, since it is a equirectangular projected 2d image
		this->SetTexture2D("u_equirectangularMap", m_mainTexture->GetID());		
		this->SetMat4("u_projectionMatrix", captureProjection);
		this->SetMat4("u_viewMatrix", captureViews[index]);
	}

	void EquirectangularToCubemapMaterial::Unuse()
	{
		Material::Unuse();
	}

	void EquirectangularToCubemapMaterial::SetMainTexture(Texture* _other)
	{
		if (this->m_mainTexture) {
			delete this->m_mainTexture;
		}
		this->m_mainTexture = _other;
	}
}