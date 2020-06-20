#include "CookTorranceMaterial.hpp"

#include "Scene.hpp"

namespace TinySandbox
{
	CookTorranceMaterial::CookTorranceMaterial()
		: BaseMaterial(nullptr, "../Shaders/Regular.vert", "", "../Shaders/CookTorrance.frag")
	{
		SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
		m_cubemapTexture = Scene::GetSkybox()->GetMainTexture();

		// TODO: Get BRDF Look Up Table Texture
		m_brdfTexture = nullptr;
	}

	CookTorranceMaterial::CookTorranceMaterial(Renderer* _renderer)
		: BaseMaterial(_renderer, "../Shaders/Regular.vert", "", "../Shaders/CookTorrance.frag")
	{
		SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
		m_cubemapTexture = Scene::GetSkybox()->GetMainTexture();

		// TODO: Get BRDF Look Up Table Texture
		m_brdfTexture = nullptr;
	}

	CookTorranceMaterial::CookTorranceMaterial(Renderer* _renderer, const char* _filename)
		: BaseMaterial(_renderer, "../Shaders/Regular.vert", "", "../Shaders/CookTorrance.frag")
	{
		SetMainTexture(new Texture(_filename, TextureType::TEXTURE_2D, false));
		m_cubemapTexture = Scene::GetSkybox()->GetMainTexture();

		// TODO: Get BRDF Look Up Table Texture
		m_brdfTexture = nullptr;
	}

	void CookTorranceMaterial::OnGUI()
	{

	}

	void CookTorranceMaterial::Unuse()
	{
		m_api->DisableDepthTest();
		m_api->DisableTexture2D();

		BaseMaterial::Unuse();
	}

	void CookTorranceMaterial::Use()
	{
		m_api->EnableTexture2D();
		m_api->EnableDepthTest();
		m_api->BindProgram(m_program);

		// Bind Uniform Variables
		const glm::mat4 viewMatrix = Scene::GetMainCamera()->ViewMatrix();
		const glm::mat4 projectionMatrix = Scene::GetMainCamera()->ProjectionMatrix();
		const glm::mat4 modelMatrix = m_renderer->entity->GetTransform()->toMatrix();

		this->SetMat4("u_ModelMatrix", modelMatrix);
		this->SetMat4("u_ViewMatrix", viewMatrix);
		this->SetMat4("u_ProjectionMatrix", projectionMatrix);
		this->SetFloat("u_metallic", m_metallic);
		this->SetFloat("u_roughness", m_roughness);
		this->SetFloat("u_ao", m_ambientOcculusion);
		this->SetVec3("u_tint", glm::vec3(1, 1, 1));
		this->SetTexture2D("u_albedo", GetMainTexture()->GetID());
		
		this->SetTexture2D("u_irradianceMap", m_cubemapTexture->GetID(CubemapTextureType::IRRADIANCE));
		this->SetTexture2D("u_prefilterMap", m_cubemapTexture->GetID(CubemapTextureType::PREFILTER));
		this->SetTexture2D("u_albedo", m_brdfTexture->GetID());
		this->SetVec3("u_CameraPos", Scene::GetMainCamera()->Position());
	}	
}