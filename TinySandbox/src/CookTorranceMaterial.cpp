#include "CookTorranceMaterial.hpp"

#include "Scene.hpp"

namespace TinySandbox
{
	CookTorranceMaterial::CookTorranceMaterial(Renderer* _renderer)
		: BaseMaterial(_renderer, "../Shaders/Regular.vert", "", "../Shaders/CookTorrance.frag")
	{
		SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
		m_cubemapTexture = Scene::GetSkybox()->GetMainTexture();

		// TODO
	}

	void CookTorranceMaterial::OnGUI()
	{

	}

	void CookTorranceMaterial::Unuse()
	{
		m_api->DisableDepthTest();

		BaseMaterial::Unuse();
	}

	void CookTorranceMaterial::Use()
	{
		m_api->EnableDepthTest();
		m_api->BindProgram(m_program);

		// Bind Uniform Variables
		const glm::mat4 viewMatrix = Scene::GetMainCamera()->ViewMatrix();
		const glm::mat4 projectionMatrix = Scene::GetMainCamera()->ProjectionMatrix();
		const glm::mat4 modelMatrix = m_renderer->entity->GetTransform()->toMatrix();

		this->SetMat4("u_Model", modelMatrix);
		this->SetMat4("u_View", viewMatrix);
		this->SetMat4("u_Projection", projectionMatrix);

		// TODO
	}	
}