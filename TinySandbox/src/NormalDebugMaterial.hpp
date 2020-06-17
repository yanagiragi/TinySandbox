#pragma once

#include "Material.hpp"

namespace TinySandbox
{
	class NormalDebugMaterial : public Material
	{
		public:
			NormalDebugMaterial(Renderer* _renderer)
				: Material("../Shaders/normalDebug.vert", "", "../Shaders/normalDebug.frag")
			{
				m_renderer = _renderer;
				entity = m_renderer->entity;
			}

			/*NormalDebugMaterial(const char* _vertexShaderSource, const char* _geometryShaderSource, const char* _fragmentShaderSource)
				: Material(_vertexShaderSource, _geometryShaderSource, _fragmentShaderSource)
			{

			}*/

			NormalDebugMaterial& operator=(const NormalDebugMaterial& _other)
			{
				this->m_program = _other.m_program;
				this->m_API = _other.m_API;
				this->m_renderer = _other.m_renderer;
				this->entity = _other.entity;
			}

			void OnGUI() override
			{

			}

			void Use() override
			{
				GraphicsAPI* API = GraphicsAPI::GetAPI();
				API->BindProgram(m_program);

				// Bind Uniform Variables
				const glm::mat4 viewMatrix = Scene::GetMainCamera()->ViewMatrix();
				const glm::mat4 projectionMatrix = Scene::GetMainCamera()->ProjectionMatrix();
				const glm::mat4 modelMatrix = entity->GetTransform()->toMatrix();

				this->SetMat4("u_Model", modelMatrix);
				this->SetMat4("u_View", viewMatrix);
				this->SetMat4("u_Projection", projectionMatrix);
			}
	};
}