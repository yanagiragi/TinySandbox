#pragma once

#include "Renderer.hpp"
#include "Texture.hpp"

#include <string>

#define TEXTURE_NOT_INITIALIZED 4294967294

namespace TinySandbox
{
	class Renderer;

	class BaseMaterial
	{
		public:

			BaseMaterial(Renderer* _renderer, const char* _vertexShaderSource, const char* _geometryShaderSource, const char* _fragmentShaderSouce);

			~BaseMaterial();

			// child class must override OnGUI function
			virtual void OnGUI() = 0;

			virtual void Use();
			
			virtual void Unuse();

			void SetBool(const std::string &name, bool value) const;

			void SetInt(const std::string &name, int value) const;

			void SetFloat(const std::string &name, float value) const;

			void SetVec2(const std::string &name, const glm::vec2 &value) const;

			void SetVec2(const std::string &name, float x, float y) const;

			void SetVec3(const std::string &name, const glm::vec3 &value) const;

			void SetVec3(const std::string &name, float x, float y, float z) const;

			void SetVec4(const std::string &name, const glm::vec4 &value) const;

			void SetVec4(const std::string &name, float x, float y, float z, float w) const;

			void SetMat2(const std::string &name, const glm::mat2 &mat) const;

			void SetMat3(const std::string &name, const glm::mat3 &mat) const;

			void SetMat4(const std::string &name, const glm::mat4 &mat) const;

			void SetTexture2D(const std::string &name, const unsigned int _textureId, const int _id);

			void SetTextureCubemap(const std::string &name, const unsigned int _textureId, const int _id);

			void SetTexture2D(const std::string &name, const unsigned int _textureId);

			void SetTextureCubemap(const std::string &name, const unsigned int _textureId);

			void SetMainTexture(Texture* _other);

			Texture* GetMainTexture() const { return m_mainTexture; }

			void SetRenderer(Renderer* _renderer) { m_renderer = _renderer; }

			BaseMaterial& operator=(const BaseMaterial& _other)
			{
				this->m_program = _other.m_program;
				this->m_api = _other.m_api;
				this->m_textureIncrementId = _other.m_textureIncrementId;
				
				this->SetMainTexture(new Texture(*_other.GetMainTexture()));

				return *this;
			}

			BaseMaterial& operator=(BaseMaterial&& _other)
			{
				this->m_program = std::move(_other.m_program);
				this->m_api = std::move(_other.m_api);
				this->m_textureIncrementId = std::move(_other.m_textureIncrementId);

				_other.m_api = nullptr;
				this->m_program = TEXTURE_NOT_INITIALIZED;
				this->m_textureIncrementId = 0;

				this->SetMainTexture(_other.GetMainTexture());

				return *this;
			}

			glm::vec2 GetTiling() const { return m_tiling; }
			void SetTiling(glm::vec2 _other) { m_tiling = _other; }

			glm::vec2 GetOffset() const { return m_offset; }
			void SetOffset(glm::vec2 _other) { m_offset = _other; }

		private:
			
			void Compile();

			std::string m_vertexShaderSource = "";
			std::string m_geometryShaderSource = "";
			std::string m_fragmentShaderSource = "";

		protected:
		
			Renderer* m_renderer; // current only support one renderer per material
			Texture* m_mainTexture;
			glm::vec2 m_tiling;
			glm::vec2 m_offset;
			unsigned int m_textureIncrementId = 0;
			unsigned int m_program;
			GraphicsAPI* m_api;
	};
}
