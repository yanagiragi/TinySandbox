#pragma once

#include "BaseMaterial.hpp"
#include "GraphicsAPI.hpp"
#include "Texture.hpp"

#include "BRDFLutGenerator.hpp"

namespace TinySandbox
{
	class UnlitMaterial : public BaseMaterial
	{
		public:

			UnlitMaterial() : BaseMaterial(nullptr, "../Shaders/unlit.vert", "", "../Shaders/unlit.frag")
			{
				SetMainTexture(new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false));
			}

			UnlitMaterial(Renderer* _renderer) : BaseMaterial(_renderer, "../Shaders/unlit.vert", "", "../Shaders/unlit.frag")
			{
				SetMainTexture( new Texture("../Resources/white.png", TextureType::TEXTURE_2D, false) );
			}

			UnlitMaterial(const char* _filename, bool isHdr) : BaseMaterial(nullptr, "../Shaders/unlit.vert", "", "../Shaders/unlit.frag")
			{
				SetMainTexture(new Texture(_filename, TextureType::TEXTURE_2D, false));
			}

			UnlitMaterial(Renderer* _renderer, const char* _filename) : BaseMaterial(_renderer, "../Shaders/unlit.vert", "", "../Shaders/unlit.frag")
			{
				SetMainTexture( new Texture(_filename, TextureType::TEXTURE_2D, false) );
			}

			UnlitMaterial(Renderer* _renderer, const char* _filename, bool isHdr) : BaseMaterial(_renderer, "../Shaders/unlit.vert", "", "../Shaders/unlit.frag")
			{
				SetMainTexture(new Texture(_filename, TextureType::TEXTURE_2D, false));
			}

			void OnGUI() override
			{

			}

			void Unuse() override
			{
				m_api->DisableDepthTest();
				m_api->DisableTexture2D();

				BaseMaterial::Unuse();
			}

			void Use() override
			{
				m_api->BindProgram(m_program);
				m_api->EnableTexture2D();
				m_api->EnableDepthTest();

				// Bind Uniform Variables
				const glm::mat4 viewMatrix = Scene::GetMainCamera()->ViewMatrix();
				const glm::mat4 projectionMatrix = Scene::GetMainCamera()->ProjectionMatrix();
				const glm::mat4 modelMatrix = m_renderer->entity->GetTransform()->toMatrix();

				this->SetMat4("u_ModelMatrix", modelMatrix);
				this->SetMat4("u_ViewMatrix", viewMatrix);
				this->SetMat4("u_ProjectionMatrix", projectionMatrix);
				this->SetTexture2D("u_albedo", GetMainTexture()->GetID());
				this->SetVec2("u_offset", m_offset.x, m_offset.y);
				this->SetVec2("u_tiling", m_tiling.x, m_tiling.y);
				this->SetVec3("u_tint", 1.0, 1.0, 1.0);
				this->SetFloat("u_alpha", 1.0);
				this->SetFloat("u_emission", 1.0);
			}

		private:
	};
}
