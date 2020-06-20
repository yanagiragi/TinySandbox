#pragma once

#include "BaseMaterial.hpp"

namespace TinySandbox
{
	class NormalDebugMaterial : public BaseMaterial
	{
		public:
			NormalDebugMaterial()
				: BaseMaterial(nullptr, "../Shaders/normalDebug.vert", "", "../Shaders/normalDebug.frag")
			{
				
			}

			NormalDebugMaterial(Renderer* _renderer)
				: BaseMaterial(nullptr, "../Shaders/normalDebug.vert", "", "../Shaders/normalDebug.frag")
			{

			}

			NormalDebugMaterial& operator=(const NormalDebugMaterial& _other)
			{
				this->m_program = _other.m_program;
				this->m_api = _other.m_api;
			}

			void OnGUI() override
			{

			}

			void Unuse() override
			{
				m_api->DisableDepthTest();

				BaseMaterial::Unuse();
			}

			void Use() override
			{
				m_api->EnableDepthTest();
				m_api->BindProgram(m_program);

				// Bind Uniform Variables
				const glm::mat4 viewMatrix = Scene::GetMainCamera()->ViewMatrix();
				const glm::mat4 projectionMatrix = Scene::GetMainCamera()->ProjectionMatrix();
				const glm::mat4 modelMatrix = m_renderer->entity->GetTransform()->toMatrix();

				this->SetMat4("u_ModelMatrix", modelMatrix);
				this->SetMat4("u_ViewMatrix", viewMatrix);
				this->SetMat4("u_ProjectionMatrix", projectionMatrix);
			}
	};
}