#pragma once

#include "GraphicsAPI.hpp"

namespace TinySandbox
{
	class GraphicsAPI_OpenGL : public GraphicsAPI
	{
	public:
		// bind "this" to GraphicsAPI::m_api
		// if multiple api instances exists, you should explicitly call SetAPI() instead.
		GraphicsAPI_OpenGL() : GraphicsAPI(this) {}

		float GetType(GraphicsAPI_DataType _type) const override;
		
		void SetupVAO(unsigned int* _VAO, Mesh* _mesh, GraphicsAPI_DataType _type) const override;

	private:
		void GenerateBuffers(unsigned int* _ids, int _length) const override;
		void BindBuffer(GraphicsAPI_DataType _type, unsigned int _id) const override;
		void UnbindBuffer(GraphicsAPI_DataType _type) const override;
		void SetBuffers(GraphicsAPI_DataType _type, size_t _size, const void *_data, GraphicsAPI_DataType _additionalType) const override;

		void GenerateVertexArrays(unsigned int* _ids, int _length) const override;
		void BindVertexArray(unsigned int _id) const override;
		void UnbindVertexArray() const override;
		void EnableVertexArrayAttribute(unsigned int _VAOid) const override;
		void DisableVertexArrayAttribute(unsigned int _VAOid) const override;
		void SetVertexArray(unsigned int _VAOid, unsigned int _size, GraphicsAPI_DataType _type, GraphicsAPI_DataType _normalized, unsigned int _stride, const void* ptr) const override;
		unsigned int CompileShader(std::string _vertexShaderSource, std::string _geometryShaderSource, std::string _fragmentShaderSouce) const override;
		void BindProgram(unsigned int _program) const override;
		void UnbindProgram() const override;

		void SetBool(unsigned int _program, const std::string &name, bool value) const override;
		void SetInt(unsigned int _program, const std::string &name, int value) const override;
		void SetFloat(unsigned int _program, const std::string &name, float value) const override;
		void SetVec2(unsigned int _program, const std::string &name, const glm::vec2 &value) const override;
		void SetVec2(unsigned int _program, const std::string &name, float x, float y) const override;
		void SetVec3(unsigned int _program, const std::string &name, const glm::vec3 &value) const override;
		void SetVec3(unsigned int _program, const std::string &name, float x, float y, float z) const override;
		void SetVec4(unsigned int _program, const std::string &name, const glm::vec4 &value) const override;
		void SetVec4(unsigned int _program, const std::string &name, float x, float y, float z, float w) const override;
		void SetMat2(unsigned int _program, const std::string &name, const glm::mat2 &mat) const override;
		void SetMat3(unsigned int _program, const std::string &name, const glm::mat3 &mat) const override;
		void SetMat4(unsigned int _program, const std::string &name, const glm::mat4 &mat) const override;

		void ClearScreenColor() const override;
		void ClearScreenDepth() const override;
		void ClearScreenStencil() const override;

		void EnableDepthTest() const override;
		void DisableDepthTest() const override;
		void SetDepthMask(GraphicsAPI_DataType _type) const override;
		void SetDepthTestMode(GraphicsAPI_DataType _type) const override;

		void EnableStencilTest() const override;
		void DisableStencilTest() const override;
		void SetStencilMask(unsigned int _mask) const override;
		
		// TODO: https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glStencilFunc.xml
		// TODO: https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glStencilOp.xml

		void EnableBlending() const override;
		void DisableBlending() const override;
		void SetBlendingMode(GraphicsAPI_DataType _type, GraphicsAPI_DataType _additionalType) const override;

		void EnableCulling() const override;
		void DisableCulling() const override;
		void SetCullingMode(GraphicsAPI_DataType _type) const override;

		void DrawArrays(GraphicsAPI_DataType _type, unsigned int _count, int _first = 0) const override;

		void GenerateTextures(unsigned int* _ids, unsigned int _length) const override;
		void BindTexture(GraphicsAPI_DataType _type, unsigned int _id) const override;
		void SetTexture2D(
			GraphicsAPI_DataType _targetType,
			unsigned int _level,
			GraphicsAPI_DataType _channelType, 
			unsigned int _width,
			unsigned int _height,
			int _border,
			GraphicsAPI_DataType _formatType,
			GraphicsAPI_DataType _type,
			const void* _data
		) const override;
		void SetTextureParameter(GraphicsAPI_DataType _targetType, GraphicsAPI_DataType _pname, GraphicsAPI_DataType _param) const override;
		void ActiveTexture(unsigned int _texture) const override;

		void EnableTexture2D() const override;
		void DisableTexture2D() const override;
		void UnbindTexture2D() const override;
		void EnableSeamlessCubemap() const override;
		void DisableSeamlessCubemap() const override;

		void GenerateFrameBuffers(unsigned int* _ids, unsigned int _length) const override;
		void BindFrameBuffer(GraphicsAPI_DataType _type, unsigned int _id) const override;
		void UnbindFrameBuffer(GraphicsAPI_DataType _type) const override;
		void AttachRenderBufferToFrameBuffer(GraphicsAPI_DataType _target, GraphicsAPI_DataType _attachment, GraphicsAPI_DataType _renderBufferTarget, unsigned int _renderBuffer) const override;

		void GenerateRenderBuffers(unsigned int* _ids, unsigned int _length) const override;
		void BindRenderBuffer(GraphicsAPI_DataType _type, unsigned int _id) const override;
		void UnbindRenderBuffer(GraphicsAPI_DataType _type) const override;
		void SetRenderBuffer(GraphicsAPI_DataType _target, GraphicsAPI_DataType _internalFormat, unsigned int _width, unsigned int _height) const override;
	};
}
