#pragma once

#include "GraphicsAPI.hpp"
#include "Component.hpp"
#include "Scene.hpp"
//#include "Renderer.hpp"

#include <string>

namespace TinySandbox
{
	class Renderer;

	class Material : public Component
	{
		public:

			Material(const char* _vertexShaderSource, const char* _geometryShaderSource, const char* _fragmentShaderSouce) 
				: m_vertexShaderSource(_vertexShaderSource), 
				m_geometryShaderSource(_geometryShaderSource), 
				m_fragmentShaderSource(_fragmentShaderSouce), 
				m_renderer(nullptr)
			{
				m_API = GraphicsAPI::GetAPI();				
				this->Compile();
			}

			void Start() override {}

			void Update() override {}

			void OnRender() override {}

			// child class must override OnGUI function
			virtual void OnGUI() override = 0;

			virtual void Use() = 0;
			
			virtual void Unuse() {
				m_API->UnbindProgram();
			}

			void SetBool(const std::string &name, bool value) const
			{
				m_API->SetBool(m_program, name, value);
			}

			void SetInt(const std::string &name, int value) const
			{
				m_API->SetInt(m_program, name, value);
			}

			void SetFloat(const std::string &name, float value) const
			{
				m_API->SetFloat(m_program, name, value);
			}

			void SetVec2(const std::string &name, const glm::vec2 &value) const
			{
				m_API->SetVec2(m_program, name, value);
			}

			void SetVec2(const std::string &name, float x, float y) const
			{
				m_API->SetVec2(m_program, name, x, y);
			}

			void SetVec3(const std::string &name, const glm::vec3 &value) const
			{
				m_API->SetVec3(m_program, name, value);
			}

			void SetVec3(const std::string &name, float x, float y, float z) const
			{
				m_API->SetVec3(m_program, name, x, y, z);
			}

			void SetVec4(const std::string &name, const glm::vec4 &value) const
			{
				m_API->SetVec4(m_program, name, value);
			}

			void SetVec4(const std::string &name, float x, float y, float z, float w) const
			{
				m_API->SetVec4(m_program, name, x, y, z, w);
			}

			void SetMat2(const std::string &name, const glm::mat2 &mat) const
			{
				m_API->SetMat2(m_program, name, mat);
			}

			void SetMat3(const std::string &name, const glm::mat3 &mat) const
			{
				m_API->SetMat3(m_program, name, mat);
			}

			void SetMat4(const std::string &name, const glm::mat4 &mat) const
			{
				m_API->SetMat4(m_program, name, mat);
			}

		private:
			
			void Compile() {
				GraphicsAPI* API = GraphicsAPI::GetAPI();
				m_program = API->CompileShader(m_vertexShaderSource, m_geometryShaderSource, m_fragmentShaderSource);
			}

			std::string m_vertexShaderSource = "";
			std::string m_geometryShaderSource = "";
			std::string m_fragmentShaderSource = "";

		protected:

			Renderer* m_renderer;
			unsigned int m_program;
			GraphicsAPI* m_API;
	};
}
