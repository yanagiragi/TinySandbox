#pragma once

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
			virtual int GetType(GraphicsAPI_DataType _type) = 0;

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
			
		private:
            static GraphicsAPI_Type m_type;
			static GraphicsAPI* m_api;
    };
}
