#pragma once

#include "Material.hpp"
#include "Texture.hpp"

#include "../includes/glad/glad.h"

namespace TinySandbox
{
	class UnlitMaterial : public Material
	{
		public:
			UnlitMaterial(Renderer* _renderer) : Material("../Shaders/unlit.vert", "", "../Shaders/unlit.frag")
			{
				m_renderer = _renderer;
				m_mainTexture = new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false);
			}

			UnlitMaterial(Renderer* _renderer, const char* _filename) : Material("../Shaders/unlit.vert", "", "../Shaders/unlit.frag")
			{
				m_renderer = _renderer;
				m_mainTexture = new Texture(_filename, TextureType::TEXTURE_2D, false);
			}

			UnlitMaterial& operator=(const UnlitMaterial& _other)
			{
				this->m_program = _other.m_program;
				this->m_api = _other.m_api;
				this->m_mainTexture = _other.m_mainTexture;
			}

			void OnGUI() override
			{

			}

			void Unuse() override
			{
				m_api->DisableTexture2D();

				Material::Unuse();
			}

			void Use() override
			{
				m_api->BindProgram(m_program);
				m_api->EnableTexture2D();

				// Bind Uniform Variables
				const glm::mat4 viewMatrix = Scene::GetMainCamera()->ViewMatrix();
				const glm::mat4 projectionMatrix = Scene::GetMainCamera()->ProjectionMatrix();
				const glm::mat4 modelMatrix = m_renderer->entity->GetTransform()->toMatrix();

				this->SetMat4("u_ModelMatrix", modelMatrix);
				this->SetMat4("u_ViewMatrix", viewMatrix);
				this->SetMat4("u_ProjectionMatrix", projectionMatrix);
				this->SetTexture2D("u_albedo", m_mainTexture->GetID());
				this->SetVec2("u_tiling", 1.0, 1.0);
				this->SetVec3("u_tint", 1.0, 1.0, 1.0);
				this->SetFloat("u_alpha", 1.0);
				this->SetFloat("u_emission", 1.0);

				glEnable(GL_TEXTURE_2D);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_mainTexture->GetID());
				glUniform1i(glGetUniformLocation(m_program, "u_albedo"), 0);
			}

		private:
			Texture* m_mainTexture;
	};
}
