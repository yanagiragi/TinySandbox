#include "CookTorranceMaterial.hpp"

#include "Scene.hpp"
#include "BRDFLutGenerator.hpp"

#include "DirectionalLight.hpp"

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
		m_tint = glm::vec3(1, 1, 1);
	}

	CookTorranceMaterial::CookTorranceMaterial(Renderer* _renderer)
		: BaseMaterial(_renderer, "../Shaders/Regular.vert", "", "../Shaders/CookTorrance.frag")
	{
		SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
		m_cubemapTexture = nullptr;

		m_roughness = 0.0;
		m_metallic = 0.0;
		m_ambientOcculusion = 1.0;
		m_tint = glm::vec3(1, 1, 1);
	}

	CookTorranceMaterial::CookTorranceMaterial(Renderer* _renderer, const char* _filename)
		: BaseMaterial(_renderer, "../Shaders/Regular.vert", "", "../Shaders/CookTorrance.frag")
	{
		SetMainTexture(new Texture(_filename, TextureType::TEXTURE_2D, false));
		m_cubemapTexture = nullptr;

		m_roughness = 0.0;
		m_metallic = 0.0;
		m_ambientOcculusion = 1.0;
		m_tint = glm::vec3(1, 1, 1);
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

		this->SetVec3("u_tint", m_tint);
		this->SetTexture2D("u_albedo", GetMainTexture()->GetID());
		
		this->SetTextureCubemap("u_irradianceMap", m_cubemapTexture->GetID(CubemapTextureType::IRRADIANCE));
		this->SetTextureCubemap("u_prefilterMap", m_cubemapTexture->GetID(CubemapTextureType::PREFILTER));
		this->SetTexture2D("u_brdfLUT", BRDFLutGenerator::GetLutID());

		this->SetVec3("u_CameraPos", Scene::GetMainCamera()->Position());

		auto lightList = Scene::GetLightList();

		for (int i = 0; i < m_api->Max_Supported_Light; ++i)
		{
			if (i >= lightList.size()) {
				this->SetFloat("u_lightIntensity[" + std::to_string(i) + "]", 0);
				this->SetVec3("u_lightColor[" + std::to_string(i) + "]", glm::vec3(0, 0, 0));
				this->SetVec3("u_lightPosition[" + std::to_string(i) + "]", glm::vec3(0, 0, 0));
				this->SetInt("u_lightType[" + std::to_string(i) + "]", static_cast<int>(Light_Type::LEN));
				this->SetVec4("u_lightAdditional[" + std::to_string(i) + "]", glm::vec4(0, 0, 0, 0));
			}
			else {

				BaseLight* light = lightList[i];

				this->SetFloat("u_lightIntensity[" + std::to_string(i) + "]", light->GetIntensity());
				this->SetVec3("u_lightColor[" + std::to_string(i) + "]", light->GetColor());
				this->SetVec3("u_lightPosition[" + std::to_string(i) + "]", light->GetPosition());

				if (dynamic_cast<DirectionalLight*>(light)) {
					this->SetInt("u_lightType[" + std::to_string(i) + "]", static_cast<int>(Light_Type::DIRECTIONAL));

					glm::vec3 rotation = light->GetRotation();
					glm::mat4 rotationMatrix = glm::mat4(1.0);
					rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
					rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
					rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));

					glm::vec4 direction = rotationMatrix * glm::vec4(1, 0, 0, 1.0);

					this->SetVec4("u_lightAdditional[" + std::to_string(i) + "]", direction);
				}
				/*
				// Un-implementated Features
				else if (dynamic_cast<PointLight*>(light)) {
					PointLight* pl = dynamic_cast<PointLight*>(light);
					this->SetInt("u_lightType[" + std::to_string(i) + "]", static_cast<int>(Light_Type::POINT));
					this->SetVec4("u_lightAdditional[" + std::to_string(i) + "]", glm::vec4(pl->Range(), 0.0, 0.0, 1.0));
				}
				else if (dynamic_cast<SpotLight*>(light)) {
					SpotLight* spl = dynamic_cast<SpotLight*>(light);
					this->SetInt("u_lightType[" + std::to_string(i) + "]", static_cast<int>(Light_Type::SPOTLIGHT));
					this->SetVec4("u_lightAdditional[" + std::to_string(i) + "]", glm::vec4(spl->Range(), spl->HoriztonalAngle(), spl->VerticalAngle(), 1.0));
				}
				*/
				else {
					throw "Error Occurs When Passing Light to Cook Torrance, Are you using un-implementated feature?";
				}
			}
		}
	}	
}