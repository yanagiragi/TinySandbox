#include "SkyboxMaterial.hpp"

#include "Scene.hpp"
#include "Texture.hpp"

namespace TinySandbox
{	
	SkyboxMaterial::SkyboxMaterial(Renderer* _renderer) : BaseMaterial(_renderer, "../Shaders/skybox.vert", "", "../Shaders/skybox.frag")
	{
		SetMainTexture( new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false) );
		m_mode = Skybox_DisplayType::REGULAR;
		m_lod = 0;
	}

	SkyboxMaterial::SkyboxMaterial(Renderer* _renderer, const char* _filename, bool _isHDR) : BaseMaterial(_renderer, "../Shaders/skybox.vert", "", "../Shaders/skybox.frag")
	{
		m_renderer = _renderer;
		SetMainTexture(new Texture(_filename, TextureType::TEXTURE_2D, _isHDR));
		m_mode = Skybox_DisplayType::REGULAR;
		m_lod = 0;
	}

	SkyboxMaterial& SkyboxMaterial::operator=(const SkyboxMaterial& _other)
	{
		BaseMaterial::operator=(_other);

		this->m_mode = _other.m_mode;
		this->m_lod = _other.m_lod;

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
		this->SetFloat("u_lod", m_lod);
		
		if (m_mode == Skybox_DisplayType::REGULAR) {
			this->SetTextureCubemap("u_environmentMap", GetMainTexture()->GetID(CubemapTextureType::REGULAR));
		}
		else if (m_mode == Skybox_DisplayType::IRRADIANCE) {
			this->SetTextureCubemap("u_environmentMap", GetMainTexture()->GetID(CubemapTextureType::IRRADIANCE));
		}
		else if (m_mode == Skybox_DisplayType::PREFILTER) {
			this->SetTextureCubemap("u_environmentMap", GetMainTexture()->GetID(CubemapTextureType::PREFILTER));
		}
		else {
			throw "Error Skybox Display Type!";
		}		
	}
}
