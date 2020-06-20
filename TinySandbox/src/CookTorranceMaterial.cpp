#include "CookTorranceMaterial.hpp"

#include "Scene.hpp"
#include "BRDFLutGenerator.hpp"

float time = 0;

namespace TinySandbox
{
	CookTorranceMaterial::CookTorranceMaterial()
		: BaseMaterial(nullptr, "../Shaders/Regular.vert", "", "../Shaders/CookTorrance.frag")
	{
		SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
		m_cubemapTexture = nullptr;
		
		m_roughness = 0.0;
		m_metallic = 0.0;
		m_ambientOcculusion = 1.0;
	}

	CookTorranceMaterial::CookTorranceMaterial(Renderer* _renderer)
		: BaseMaterial(_renderer, "../Shaders/Regular.vert", "", "../Shaders/CookTorrance.frag")
	{
		SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
		m_cubemapTexture = nullptr;

		m_roughness = 0.0;
		m_metallic = 0.0;
		m_ambientOcculusion = 1.0;
	}

	CookTorranceMaterial::CookTorranceMaterial(Renderer* _renderer, const char* _filename)
		: BaseMaterial(_renderer, "../Shaders/Regular.vert", "", "../Shaders/CookTorrance.frag")
	{
		SetMainTexture(new Texture(_filename, TextureType::TEXTURE_2D, false));
		m_cubemapTexture = nullptr;

		m_roughness = 0.0;
		m_metallic = 0.0;
		m_ambientOcculusion = 1.0;
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
		if (m_cubemapTexture == nullptr)
		{
			m_cubemapTexture = Scene::GetSkybox()->GetMainTexture();
		}

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
		
		this->SetTextureCubemap("u_irradianceMap", m_cubemapTexture->GetID(CubemapTextureType::IRRADIANCE));
		this->SetTextureCubemap("u_prefilterMap", m_cubemapTexture->GetID(CubemapTextureType::PREFILTER));
		this->SetTexture2D("u_brdfLUT", BRDFLutGenerator::GetLutID());

		this->SetVec3("u_CameraPos", Scene::GetMainCamera()->Position());

		// TODO
		this->SetFloat("u_lightIntensity", 1.0);
		this->SetVec3("u_lightColor", glm::vec3(1.0, 1.0, 1.0));
		this->SetVec3("u_lightPosition", glm::vec3(0, 0, 5));		
	}	
}