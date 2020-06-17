#include "GraphicsAPI_OpenGL.hpp"
#include <assert.h>
#include <glad/glad.h>

using namespace TinySandbox;

int GraphicsAPI_OpenGL::GetType(GraphicsAPI_DataType _dataType)
{
	int type = -2147483648; // magic number

	switch (_dataType)
	{
		case GraphicsAPI_DataType::BYTE:
			type = GL_BYTE; break;

		case GraphicsAPI_DataType::UNSIGNED_BYTE:
			type = GL_UNSIGNED_BYTE; break;

		case GraphicsAPI_DataType::SHORT:
			type = GL_SHORT; break;

		case GraphicsAPI_DataType::UNSIGNED_SHORT:
			type = GL_UNSIGNED_SHORT; break;

		case GraphicsAPI_DataType::INT:
			type = GL_INT; break;

		case GraphicsAPI_DataType::UNSIGNED_INT:
			type = GL_UNSIGNED_INT; break;

		case GraphicsAPI_DataType::HALF_FLOAT:
			type = GL_HALF_FLOAT; break;

		case GraphicsAPI_DataType::FLOAT:
			type = GL_FLOAT; break;

		case GraphicsAPI_DataType::DOUBLE:
			type = GL_DOUBLE; break;

		
		case GraphicsAPI_DataType::TRUE:
			type = GL_TRUE; break;

		case GraphicsAPI_DataType::FALSE:
			type = GL_FALSE; break;

		case GraphicsAPI_DataType::ARRAY_BUFFER:
			type = GL_ARRAY_BUFFER; break;		

		case GraphicsAPI_DataType::ELEMENT_ARRAY_BUFFER:
			type = GL_ELEMENT_ARRAY_BUFFER; break;

		case GraphicsAPI_DataType::PIXEL_PACK_BUFFER:
			type = GL_PIXEL_PACK_BUFFER; break;

		case GraphicsAPI_DataType::PIXEL_UNPACK_BUFFER:
			type = GL_PIXEL_UNPACK_BUFFER; break;	

		case GraphicsAPI_DataType::TRANSFORM_FEEDBACK_BUFFER:
			type = GL_TRANSFORM_FEEDBACK_BUFFER; break;
	
		case GraphicsAPI_DataType::STREAM_DRAW:
			type = GL_STREAM_DRAW; break;

		case GraphicsAPI_DataType::STREAM_READ:
			type = GL_STREAM_READ; break;

		case GraphicsAPI_DataType::STREAM_COPY:
			type = GL_STREAM_COPY; break;

		case GraphicsAPI_DataType::STATIC_DRAW:
			type = GL_STATIC_DRAW; break;

		case GraphicsAPI_DataType::STATIC_READ:
			type = GL_STATIC_READ; break;

		case GraphicsAPI_DataType::STATIC_COPY:
			type = GL_STATIC_COPY; break;

		case GraphicsAPI_DataType::DYNAMIC_DRAW:
			type = GL_DYNAMIC_DRAW; break;

		case GraphicsAPI_DataType::DYNAMIC_READ:
			type = GL_DYNAMIC_READ; break;

		case GraphicsAPI_DataType::DYNAMIC_COPY:
			type = GL_DYNAMIC_COPY; break;

		/* OpenGL 4.4 Contexts */

		case GraphicsAPI_DataType::FIXED:
			type = GL_FIXED; break;

		case GraphicsAPI_DataType::ATOMIC_COUNTER_BUFFER:
			type = GL_ATOMIC_COUNTER_BUFFER; break;

		case GraphicsAPI_DataType::COPY_READ_BUFFER:
			type = GL_COPY_READ_BUFFER; break;

		case GraphicsAPI_DataType::COPY_WRITE_BUFFER:
			type = GL_COPY_WRITE_BUFFER; break;

		case GraphicsAPI_DataType::DISPATCH_INDIRECT_BUFFER:
			type = GL_DISPATCH_INDIRECT_BUFFER; break;

		case GraphicsAPI_DataType::DRAW_INDIRECT_BUFFER:
			type = GL_DRAW_INDIRECT_BUFFER; break;

		case GraphicsAPI_DataType::QUERY_BUFFER:
			type = GL_QUERY_BUFFER; break;

		case GraphicsAPI_DataType::SHADER_STORAGE_BUFFER:
			type = GL_SHADER_STORAGE_BUFFER; break;

		case GraphicsAPI_DataType::TEXTURE_BUFFER:
			type = GL_TEXTURE_BUFFER; break;

		case GraphicsAPI_DataType::UNIFORM_BUFFER:
			type = GL_UNIFORM_BUFFER; break;


		default: break;
	}

	// check if fails
	assert (type != -2147483648);

	return type;
}

void GraphicsAPI_OpenGL::GenerateBuffers(unsigned int* _ids, int _length)
{
	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml
	glGenBuffers(_length, _ids);
}

void GraphicsAPI_OpenGL::BindBuffer(GraphicsAPI_DataType _type, unsigned int _id)
{
	const GLenum target = static_cast<GLenum>(this->GetType(_type));
	const GLuint buffer = static_cast<GLuint>(_id);
	
	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
	glBindBuffer(target, buffer);
}

void GraphicsAPI_OpenGL::UnbindBuffer(GraphicsAPI_DataType _type)
{
	BindBuffer(_type, NULL);
}

void GraphicsAPI_OpenGL::SetBuffers(GraphicsAPI_DataType _type, size_t _size, const void *_data, GraphicsAPI_DataType _additionalType)
{
	// GLenum is a 32-bit integer
	const GLenum target = static_cast<GLenum>(this->GetType(_type));

	// GLsizeiptr is ptrbits, the bitdepth of a CPU pointer address
	// Reference: https://www.khronos.org/opengl/wiki/OpenGL_Type
	const GLsizeiptr size = static_cast<GLsizeiptr>(_size);

	const GLenum usage = static_cast<GLenum>(this->GetType(_additionalType));

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
	glBufferData(target, size, _data, usage);
}

void GraphicsAPI_OpenGL::EnableVertexArrayAttribute(unsigned int _VAOid) 
{
	const GLuint index = static_cast<GLuint>(_VAOid);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
	glEnableVertexAttribArray(index);
}

void GraphicsAPI_OpenGL::DisableVertexArrayAttribute(unsigned int _VAOid)
{
	const GLuint index = static_cast<GLuint>(_VAOid);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
	glDisableVertexAttribArray(index);
}

void GraphicsAPI_OpenGL::SetVertexArray(unsigned int _VAOid, unsigned int _size, GraphicsAPI_DataType _type, GraphicsAPI_DataType _normalized, unsigned int _stride, const void* ptr)
{
	const GLuint index = static_cast<GLuint>(_VAOid);
	const GLint size = static_cast<GLint>(_size);
	const GLenum type = static_cast<GLenum>(GetType(_type));
	const GLboolean normalized = static_cast<GLboolean>(GetType(_normalized));
	const GLsizei stride = static_cast<GLsizei>(_stride);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(index, size, type, normalized, stride, ptr);
}

void GraphicsAPI_OpenGL::BindVertexArray(unsigned int _id)
{
	const GLuint array = static_cast<GLuint>(_id);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml
	glBindVertexArray(array);
}

void GraphicsAPI_OpenGL::UnbindVertexArray()
{
	BindVertexArray(NULL);
}

void GraphicsAPI_OpenGL::GenerateVertexArrays(unsigned int* _ids, int _length)
{
	const GLsizei n = static_cast<GLsizei>(_length);
	GLuint* arrays = static_cast<GLuint*> (_ids);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
	glGenVertexArrays(n, arrays);
}

void GraphicsAPI_OpenGL::SetupVAO(unsigned int* _VAO, Mesh* _mesh, GraphicsAPI_DataType _type)
{
	const unsigned int vboSize = _mesh->dataSize;
	const size_t vec3Size = _mesh->GetVec3Size();
	const size_t vec2Size = _mesh->GetVec2Size();

	// Setup VBO
	GLuint* VBO = new GLuint[vboSize];		
	GenerateBuffers(VBO, vboSize);

	BindBuffer(GraphicsAPI_DataType::ARRAY_BUFFER, VBO[0]);	
	SetBuffers(GraphicsAPI_DataType::ARRAY_BUFFER, vec3Size * _mesh->vertex.size(), _mesh->vertex.data(), _type);

	BindBuffer(GraphicsAPI_DataType::ARRAY_BUFFER, VBO[1]);
	SetBuffers(GraphicsAPI_DataType::ARRAY_BUFFER, vec3Size * _mesh->vertex.size(), _mesh->normal.data(), _type);

	BindBuffer(GraphicsAPI_DataType::ARRAY_BUFFER, VBO[2]);
	SetBuffers(GraphicsAPI_DataType::ARRAY_BUFFER, vec2Size * _mesh->vertex.size(), _mesh->uv0.data(), _type);

	// Bind VBO to VAO
	GenerateVertexArrays(_VAO, 1);
	BindVertexArray(*_VAO);

	EnableVertexArrayAttribute(0);
	BindBuffer(GraphicsAPI_DataType::ARRAY_BUFFER, VBO[0]); // vertices
	SetVertexArray(0, 3, GraphicsAPI_DataType::FLOAT, GraphicsAPI_DataType::FALSE, 0, 0);
	
	EnableVertexArrayAttribute(1);
	BindBuffer(GraphicsAPI_DataType::ARRAY_BUFFER, VBO[1]); // normal
	SetVertexArray(1, 3, GraphicsAPI_DataType::FLOAT, GraphicsAPI_DataType::FALSE, 0, 0);

	EnableVertexArrayAttribute(2);
	BindBuffer(GraphicsAPI_DataType::ARRAY_BUFFER, VBO[2]); // uv0
	SetVertexArray(2, 2, GraphicsAPI_DataType::FLOAT, GraphicsAPI_DataType::FALSE, 0, 0);

	// Cleanup resources & Unbind all	
	UnbindVertexArray();
	for (auto i = 0; i < vboSize; ++i) {
		DisableVertexArrayAttribute(i);
	}
	UnbindBuffer(GraphicsAPI_DataType::ARRAY_BUFFER);

	delete[] VBO;
}