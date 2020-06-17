#pragma once

#include <string>
#include "Mesh.hpp"

namespace TinySandbox
{
    enum class GraphicsAPI_Type
    {
        OPENGL,
        OPENGL_ES,
        DIRECT_X,
        LEN // return length of the enum class
    };

	enum class GraphicsAPI_DataType
	{
		// data type
		BYTE,
		UNSIGNED_BYTE,
		SHORT,
		UNSIGNED_SHORT,
		INT,
		UNSIGNED_INT,
		HALF_FLOAT,
		FLOAT,
		DOUBLE,
		FIXED,
		TRUE,
		FALSE,

		// Depth Func
		NEVER,
		LESS,
		EQUAL,
		LEQUAL,
		GREATER,
		NOTEQUAL,
		GEQUAL,
		ALWAYS,

		// Culling Face
		FRONT,
		BACK,
		FRONT_AND_BACK,

		// Primitive Types
		POINTS,
		LINE_STRIP,
		LINE_LOOP,
		LINES,
		LINE_STRIP_ADJACENCY,
		LINES_ADJACENCY,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		TRIANGLES,
		TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY,
		PATCHES,

		// others
		ARRAY_BUFFER,
		ATOMIC_COUNTER_BUFFER,
		COPY_READ_BUFFER,
		COPY_WRITE_BUFFER,
		DISPATCH_INDIRECT_BUFFER,
		DRAW_INDIRECT_BUFFER,
		ELEMENT_ARRAY_BUFFER,
		PIXEL_PACK_BUFFER,
		PIXEL_UNPACK_BUFFER,
		QUERY_BUFFER,
		SHADER_STORAGE_BUFFER,
		TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK_BUFFER,
		UNIFORM_BUFFER,
		STREAM_DRAW,
		STREAM_READ,
		STREAM_COPY,
		STATIC_DRAW,
		STATIC_READ,
		STATIC_COPY,
		DYNAMIC_DRAW,
		DYNAMIC_READ,
		DYNAMIC_COPY,

		// end
		LEN
	};

    class GraphicsAPI
    {
        public:
            GraphicsAPI() {
                GraphicsAPI::m_type = GraphicsAPI_Type::LEN;
            };

			GraphicsAPI (GraphicsAPI* _api) {
				GraphicsAPI::m_api = _api;
				GraphicsAPI::m_type = _api->GetType();
			};

			/*GraphicsAPI& operator= (const GraphicsAPI& _api) {
				*GraphicsAPI::m_api = _api;
				GraphicsAPI::m_type = _api.GetType();
				return (*this);
			};*/

			static void SetAPI(GraphicsAPI* _api) {
				m_api = _api;
			}

            static GraphicsAPI* GetAPI() {
				return m_api;
			}

			const GraphicsAPI_Type& GetType() const {
				return m_type;
			}

			// virtual void Init();

			// define virtual functions
			// i.e., virtual void BindTextures(Texture, uint_32t);

			// Maps GraphicsAPI_DataType to actual MACRO type
			virtual int GetType(GraphicsAPI_DataType _type) const = 0;

			virtual void GenerateBuffers(unsigned int* _ids, int _length) = 0;
			virtual void BindBuffer(GraphicsAPI_DataType _type, unsigned int _id) = 0;
			virtual void UnbindBuffer(GraphicsAPI_DataType _type) = 0;
			virtual void SetBuffers(
				GraphicsAPI_DataType _type, 
				size_t _size, 
				const void* _data, 
				GraphicsAPI_DataType _additionalType
			) = 0;

			virtual void GenerateVertexArrays(unsigned int* _ids, int _length) = 0;
			virtual void BindVertexArray(unsigned int _id) = 0;
			virtual void UnbindVertexArray() = 0;
			virtual void SetupVAO(unsigned int* _VAO, Mesh* _mesh, GraphicsAPI_DataType _type) = 0;
			
			virtual void EnableVertexArrayAttribute(unsigned int _VAOid) = 0;
			virtual void DisableVertexArrayAttribute(unsigned int _VAOid) = 0;

			virtual void SetVertexArray(unsigned int _VAOid, unsigned int _size, GraphicsAPI_DataType _type, GraphicsAPI_DataType _normalized, unsigned int _stride, const void* ptr) = 0;

			virtual unsigned int CompileShader(std::string _vertexShaderSource, std::string _geometryShaderSource, std::string _fragmentShaderSouce) = 0;

			virtual void BindProgram(unsigned int _program) = 0;
			virtual void UnbindProgram() = 0;

			// Set Uniforms
			virtual void SetBool(unsigned int _program, const std::string &name, bool value) const = 0;
			virtual void SetInt(unsigned int _program, const std::string &name, int value) const = 0;
			virtual void SetFloat(unsigned int _program, const std::string &name, float value) const = 0;
			virtual void SetVec2(unsigned int _program, const std::string &name, const glm::vec2 &value) const = 0;
			virtual void SetVec2(unsigned int _program, const std::string &name, float x, float y) const = 0;
			virtual void SetVec3(unsigned int _program, const std::string &name, const glm::vec3 &value) const = 0;
			virtual void SetVec3(unsigned int _program, const std::string &name, float x, float y, float z) const = 0;
			virtual void SetVec4(unsigned int _program, const std::string &name, const glm::vec4 &value) const = 0;
			virtual void SetVec4(unsigned int _program, const std::string &name, float x, float y, float z, float w) const = 0;
			virtual void SetMat2(unsigned int _program, const std::string &name, const glm::mat2 &mat) const = 0;
			virtual void SetMat3(unsigned int _program, const std::string &name, const glm::mat3 &mat) const = 0;
			virtual void SetMat4(unsigned int _program, const std::string &name, const glm::mat4 &mat) const = 0;

			virtual void ClearScreenColor() const = 0;
			virtual void ClearScreenDepth() const = 0;
			virtual void ClearScreenScreen() const = 0;

			virtual void EnableDepthTest() const = 0;
			virtual void DisableDepthTest() const = 0;
			virtual void SetDepthMask(GraphicsAPI_DataType _type) const = 0;
			virtual void SetDepthTestMode(GraphicsAPI_DataType _type) const = 0;
			
			virtual void EnableStencilTest() const = 0;
			virtual void DisableStencilTest() const = 0;
			virtual void SetStencilMask(unsigned int _mask) const = 0;

			virtual void EnableBlending() const = 0;
			virtual void DisableBlending() const = 0;
			virtual void SetBlendingMode(GraphicsAPI_DataType _type, GraphicsAPI_DataType _additionalType) const = 0;

			virtual void EnableCulling() const = 0;
			virtual void DisableCulling() const = 0;
			virtual void SetCullingMode(GraphicsAPI_DataType _type) const = 0;

			virtual void DrawArrays(GraphicsAPI_DataType _type, unsigned int count, int _first = 0) const = 0;
			
		private:
            static GraphicsAPI_Type m_type;
			static GraphicsAPI* m_api;
    };
}
