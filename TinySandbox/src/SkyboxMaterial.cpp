#include "SkyboxMaterial.hpp"

#include "Texture.hpp"

namespace TinySandbox
{	
	SkyboxMaterial::SkyboxMaterial(Renderer* _renderer) : BaseMaterial("../Shaders/skybox.vert", "", "../Shaders/skybox.frag")
	{
		m_renderer = _renderer;
		m_mainTexture = new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false);
		m_mode = Skybox_DisplayType::REGULAR;
	}

	SkyboxMaterial::SkyboxMaterial(Renderer* _renderer, const char* _filename, bool _isHDR) : BaseMaterial("../Shaders/skybox.vert", "", "../Shaders/skybox.frag")
	{
		m_renderer = _renderer;
		m_mainTexture = new Texture(_filename, TextureType::TEXTURE_2D, _isHDR);
		m_mode = Skybox_DisplayType::REGULAR;
	}

	SkyboxMaterial& SkyboxMaterial::operator=(const SkyboxMaterial& _other)
	{
		this->m_program = _other.m_program;
		this->m_api = _other.m_api;
		this->m_mainTexture = _other.m_mainTexture;
		this->m_mode = _other.m_mode;

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
		BaseMaterial::Unuse();
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
		
		if (m_mode == Skybox_DisplayType::REGULAR) {
			this->SetTextureCubemap("u_environmentMap", m_mainTexture->GetID(CubemapTextureType::REGULAR));
		}
		else if (m_mode == Skybox_DisplayType::IRRADIANCE) {
			this->SetTextureCubemap("u_environmentMap", m_mainTexture->GetID(CubemapTextureType::IRRADIANCE));
		}
		else if (m_mode == Skybox_DisplayType::REGULAR) {
			this->SetTextureCubemap("u_environmentMap", m_mainTexture->GetID(CubemapTextureType::PREFILTER));
		}
		else {
			throw "Error Skybox Display Type!";
		}		
	}

	void SkyboxMaterial::SetMainTexture(Texture* _other)
	{
		if (this->m_mainTexture) {
			delete this->m_mainTexture;
		}
		this->m_mainTexture = _other;
	}

	void SkyboxMaterial::SetDisplayMode(Skybox_DisplayType _mode)
	{
		m_mode = _mode;
	}

}
