#pragma once

#include "BaseMaterial.hpp"

namespace TinySandbox
{
	BaseMaterial::BaseMaterial(Renderer* _renderer, const char* _vertexShaderSource, const char* _geometryShaderSource, const char* _fragmentShaderSouce)
		: m_vertexShaderSource(_vertexShaderSource),
		m_geometryShaderSource(_geometryShaderSource),
		m_fragmentShaderSource(_fragmentShaderSouce),
		m_renderer(nullptr)
	{
		m_renderer = _renderer;
		m_api = GraphicsAPI::GetAPI();
		this->Compile();
		
		m_mainTexture = nullptr; // default is nullptr
	}

	BaseMaterial::~BaseMaterial()
	{
		if (m_mainTexture) {
			delete m_mainTexture;
		}
	}

	void BaseMaterial::Unuse() {
		m_api->UnbindProgram();
		while (m_textureIncrementId > 0) {
			m_api->ActiveTexture(m_textureIncrementId);
			m_api->UnbindTexture(GraphicsAPI_DataType::TEXTURE_2D);
			m_textureIncrementId -= 1;
		}
		m_textureIncrementId = 0;
		m_api->ActiveTexture(m_textureIncrementId);
	}

	void BaseMaterial::SetMainTexture(Texture* _other)
	{
		if (this->m_mainTexture) {
			delete this->m_mainTexture;
		}
		this->m_mainTexture = _other;
	}

	void BaseMaterial::SetBool(const std::string &name, bool value) const
	{
		m_api->SetBool(m_program, name, value);
	}

	void BaseMaterial::SetInt(const std::string &name, int value) const
	{
		m_api->SetInt(m_program, name, value);
	}

	void BaseMaterial::SetFloat(const std::string &name, float value) const
	{
		m_api->SetFloat(m_program, name, value);
	}

	void BaseMaterial::SetVec2(const std::string &name, const glm::vec2 &value) const
	{
		m_api->SetVec2(m_program, name, value);
	}

	void BaseMaterial::SetVec2(const std::string &name, float x, float y) const
	{
		m_api->SetVec2(m_program, name, x, y);
	}

	void BaseMaterial::SetVec3(const std::string &name, const glm::vec3 &value) const
	{
		m_api->SetVec3(m_program, name, value);
	}

	void BaseMaterial::SetVec3(const std::string &name, float x, float y, float z) const
	{
		m_api->SetVec3(m_program, name, x, y, z);
	}

	void BaseMaterial::SetVec4(const std::string &name, const glm::vec4 &value) const
	{
		m_api->SetVec4(m_program, name, value);
	}

	void BaseMaterial::SetVec4(const std::string &name, float x, float y, float z, float w) const
	{
		m_api->SetVec4(m_program, name, x, y, z, w);
	}

	void BaseMaterial::SetMat2(const std::string &name, const glm::mat2 &mat) const
	{
		m_api->SetMat2(m_program, name, mat);
	}

	void BaseMaterial::SetMat3(const std::string &name, const glm::mat3 &mat) const
	{
		m_api->SetMat3(m_program, name, mat);
	}

	void BaseMaterial::SetMat4(const std::string &name, const glm::mat4 &mat) const
	{
		m_api->SetMat4(m_program, name, mat);
	}

	void BaseMaterial::SetTexture2D(const std::string &name, const unsigned int _textureId)
	{
		m_api->ActiveTexture(m_textureIncrementId);
		m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_2D, _textureId);
		m_api->SetInt(m_program, name, m_textureIncrementId);

		m_textureIncrementId += 1; // auto increment id
	}

	void BaseMaterial::SetTextureCubemap(const std::string &name, const unsigned int _textureId)
	{
		m_api->ActiveTexture(m_textureIncrementId);
		m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, _textureId);
		m_api->SetInt(m_program, name, m_textureIncrementId);

		m_textureIncrementId += 1; // auto increment id
	}

	void BaseMaterial::SetTexture2D(const std::string &name, const unsigned int _textureId, const int _id)
	{
		m_api->ActiveTexture(_id);
		m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_2D, _textureId);
		m_api->SetInt(m_program, name, _id);

		m_textureIncrementId = (m_textureIncrementId > _id) ? m_textureIncrementId : _id;
	}

	void BaseMaterial::SetTextureCubemap(const std::string &name, const unsigned int _textureId, const int _id)
	{
		m_api->ActiveTexture(_id);
		m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_CUBE_MAP, _textureId);
		m_api->SetInt(m_program, name, _id);

		m_textureIncrementId = (m_textureIncrementId > _id) ? m_textureIncrementId : _id;
	}

	void BaseMaterial::Compile() {
		GraphicsAPI* API = GraphicsAPI::GetAPI();
		m_program = API->CompileShader(m_vertexShaderSource, m_geometryShaderSource, m_fragmentShaderSource);
	}		
}
