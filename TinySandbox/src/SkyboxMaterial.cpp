#include "SkyboxMaterial.hpp"

#include "Texture.hpp"

namespace TinySandbox
{	
	SkyboxMaterial::SkyboxMaterial(Renderer* _renderer) : Material("../Shaders/skybox.vert", "", "../Shaders/skybox.frag")
	{
		m_renderer = _renderer;
		m_mainTexture = new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false);
	}

	SkyboxMaterial::SkyboxMaterial(Renderer* _renderer, const char* _filename, bool _isHDR) : Material("../Shaders/skybox.vert", "", "../Shaders/skybox.frag")
	{
		m_renderer = _renderer;
		m_mainTexture = new Texture(_filename, TextureType::TEXTURE_2D, _isHDR);
	}

	SkyboxMaterial& SkyboxMaterial::operator=(const SkyboxMaterial& _other)
	{
		this->m_program = _other.m_program;
		this->m_api = _other.m_api;
		this->m_mainTexture = _other.m_mainTexture;
		
		return *this;
	}

	void SkyboxMaterial::OnGUI()
	{

	}

	void SkyboxMaterial::Unuse()
	{
		m_api->DisableTexture2D();
		m_api->DisableDepthTest();
		m_api->DisableSeamlessCubemap();
		Material::Unuse();
	}

	void SkyboxMaterial::Use()
	{
		m_api->BindProgram(m_program);

		m_api->EnableDepthTest();
		m_api->SetDepthTestMode(GraphicsAPI_DataType::LEQUAL);

		m_api->EnableTexture2D();
		m_api->EnableSeamlessCubemap();

		// Bind Uniform Variables
		const glm::mat4 viewMatrix = Scene::GetMainCamera()->ViewMatrix();
		const glm::mat4 projectionMatrix = Scene::GetMainCamera()->ProjectionMatrix();

		this->SetMat4("u_ViewMatrix", viewMatrix);
		this->SetMat4("u_ProjectionMatrix", projectionMatrix);
		this->SetTextureCubemap("u_environmentMap", m_mainTexture->GetID());
		// this->SetTexture2D("u_environmentMap", m_mainTexture->GetID());
	}

	void SkyboxMaterial::SetMainTexture(Texture* _other)
	{
		if (this->m_mainTexture) {
			delete this->m_mainTexture;
		}
		this->m_mainTexture = _other;
	}

}
