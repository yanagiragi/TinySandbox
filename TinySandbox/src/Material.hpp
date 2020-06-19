#pragma once

#include "GraphicsAPI.hpp"
#include "Component.hpp"
#include "Scene.hpp"
//#include "Renderer.hpp"

#include <string>

namespace TinySandbox
{
	class Renderer;

	class Material
	{
		public:

			Material(const char* _vertexShaderSource, const char* _geometryShaderSource, const char* _fragmentShaderSouce) 
				: m_vertexShaderSource(_vertexShaderSource), 
				m_geometryShaderSource(_geometryShaderSource), 
				m_fragmentShaderSource(_fragmentShaderSouce), 
				m_renderer(nullptr)
			{
				m_api = GraphicsAPI::GetAPI();				
				this->Compile();
			}

			// child class must override OnGUI function
			virtual void OnGUI() = 0;

			virtual void Use() = 0;
			
			virtual void Unuse() {
				m_api->UnbindProgram();
				while (m_textureIncrementId > 0) {
					m_api->ActiveTexture(m_textureIncrementId);
					m_api->UnbindTexture(GraphicsAPI_DataType::TEXTURE_2D);
					m_textureIncrementId -= 1;
				}
				m_textureIncrementId = 0;
				m_api->ActiveTexture(m_textureIncrementId);
			}

			void SetBool(const std::string &name, bool value) const
			{
				m_api->SetBool(m_program, name, value);
			}

			void SetInt(const std::string &name, int value) const
			{
				m_api->SetInt(m_program, name, value);
			}

			void SetFloat(const std::string &name, float value) const
			{
				m_api->SetFloat(m_program, name, value);
			}

			void SetVec2(const std::string &name, const glm::vec2 &value) const
			{
				m_api->SetVec2(m_program, name, value);
			}

			void SetVec2(const std::string &name, float x, float y) const
			{
				m_api->SetVec2(m_program, name, x, y);
			}

			void SetVec3(const std::string &name, const glm::vec3 &value) const
			{
				m_api->SetVec3(m_program, name, value);
			}

			void SetVec3(const std::string &name, float x, float y, float z) const
			{
				m_api->SetVec3(m_program, name, x, y, z);
			}

			void SetVec4(const std::string &name, const glm::vec4 &value) const
			{
				m_api->SetVec4(m_program, name, value);
			}

			void SetVec4(const std::string &name, float x, float y, float z, float w) const
			{
				m_api->SetVec4(m_program, name, x, y, z, w);
			}

			void SetMat2(const std::string &name, const glm::mat2 &mat) const
			{
				m_api->SetMat2(m_program, name, mat);
			}

			void SetMat3(const std::string &name, const glm::mat3 &mat) const
			{
				m_api->SetMat3(m_program, name, mat);
			}

			void SetMat4(const std::string &name, const glm::mat4 &mat) const
			{
				m_api->SetMat4(m_program, name, mat);
			}

			void SetTexture2D(const std::string &name, const unsigned int _textureId, const int _id = -1)
			{
				const int id = (_id == -1) ? m_textureIncrementId : _id;
				
				m_api->ActiveTexture(id);
				m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_2D, _textureId);
				m_api->SetInt(m_program, name, id);

				m_textureIncrementId += 1; // auto increment id
			}

			void SetTextureCubemap(const std::string &name, const unsigned int _textureId, const int _id = -1)
			{
				const int id = (_id == -1) ? m_textureIncrementId : _id;

				m_api->ActiveTexture(id);
				m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, _textureId);
				m_api->SetInt(m_program, name, id);

				m_textureIncrementId += 1; // auto increment id
			}

			// Debug Only
			GLuint program() { return m_program; }

		private:
			
			void Compile() {
				GraphicsAPI* API = GraphicsAPI::GetAPI();
				m_program = API->CompileShader(m_vertexShaderSource, m_geometryShaderSource, m_fragmentShaderSource);
			}

			std::string m_vertexShaderSource = "";
			std::string m_geometryShaderSource = "";
			std::string m_fragmentShaderSource = "";


		protected:
		
			Renderer* m_renderer; // current only support one renderer per material

			unsigned int m_textureIncrementId = 0;

			unsigned int m_program;
			GraphicsAPI* m_api;			
	};
}
