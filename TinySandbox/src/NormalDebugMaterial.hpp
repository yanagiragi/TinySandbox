#pragma once

#include "BaseMaterial.hpp"

namespace TinySandbox
{
	class NormalDebugMaterial : public BaseMaterial
	{
		public:
			NormalDebugMaterial(Renderer* _renderer)
				: BaseMaterial("../Shaders/normalDebug.vert", "", "../Shaders/normalDebug.frag")
			{
				m_renderer = _renderer;
			}

			/*NormalDebugMaterial(const char* _vertexShaderSource, const char* _geometryShaderSource, const char* _fragmentShaderSource)
				: Material(_vertexShaderSource, _geometryShaderSource, _fragmentShaderSource)
			{

			}*/

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

				this->SetMat4("u_Model", modelMatrix);
				this->SetMat4("u_View", viewMatrix);
				this->SetMat4("u_Projection", projectionMatrix);
			}
	};
}