#include "GraphicsAPI_OpenGL.hpp"

#include <glad/glad.h>
#include <assert.h>
#include <functional>


using namespace TinySandbox;

float GraphicsAPI_OpenGL::GetType(GraphicsAPI_DataType _dataType) const
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

		case GraphicsAPI_DataType::NEVER:
			type = GL_NEVER; break;

		case GraphicsAPI_DataType::LESS:
			type = GL_LESS; break;

		case GraphicsAPI_DataType::EQUAL:
			type = GL_EQUAL; break;

		case GraphicsAPI_DataType::LEQUAL:
			type = GL_LEQUAL; break;

		case GraphicsAPI_DataType::GREATER:
			type = GL_GREATER; break;

		case GraphicsAPI_DataType::NOTEQUAL:
			type = GL_NOTEQUAL; break;

		case GraphicsAPI_DataType::GEQUAL:
			type = GL_GEQUAL; break;

		case GraphicsAPI_DataType::ALWAYS:
			type = GL_ALWAYS; break;

		case GraphicsAPI_DataType::FRONT:
			type = GL_FRONT; break;

		case GraphicsAPI_DataType::BACK:
			type = GL_BACK; break;

		case GraphicsAPI_DataType::FRONT_AND_BACK:
			type = GL_FRONT_AND_BACK; break;

		case GraphicsAPI_DataType::POINTS:
			type = GL_POINTS; break;

		case GraphicsAPI_DataType::LINE_STRIP:
			type = GL_LINE_STRIP; break;

		case GraphicsAPI_DataType::LINE_LOOP:
			type = GL_LINE_LOOP; break;

		case GraphicsAPI_DataType::LINES:
			type = GL_LINES; break;

		case GraphicsAPI_DataType::LINE_STRIP_ADJACENCY:
			type = GL_LINE_STRIP_ADJACENCY; break;

		case GraphicsAPI_DataType::LINES_ADJACENCY:
			type = GL_LINES_ADJACENCY; break;

		case GraphicsAPI_DataType::TRIANGLE_STRIP:
			type = GL_TRIANGLE_STRIP; break;

		case GraphicsAPI_DataType::TRIANGLE_FAN:
			type = GL_TRIANGLE_FAN; break;

		case GraphicsAPI_DataType::TRIANGLES:
			type = GL_TRIANGLES; break;

		case GraphicsAPI_DataType::TRIANGLE_STRIP_ADJACENCY:
			type = GL_TRIANGLE_STRIP_ADJACENCY; break;

		case GraphicsAPI_DataType::TRIANGLES_ADJACENCY:
			type = GL_TRIANGLES_ADJACENCY; break;

		case GraphicsAPI_DataType::PATCHES:
			type = GL_PATCHES; break;

		case GraphicsAPI_DataType::TEXTURE_2D:
			type = GL_TEXTURE_2D; break;

		case GraphicsAPI_DataType::PROXY_TEXTURE_2D:
			type = GL_PROXY_TEXTURE_2D; break;

		case GraphicsAPI_DataType::TEXTURE_1D_ARRAY:
			type = GL_TEXTURE_1D_ARRAY; break;

		case GraphicsAPI_DataType::PROXY_TEXTURE_1D_ARRAY:
			type = GL_PROXY_TEXTURE_1D_ARRAY; break;

		case GraphicsAPI_DataType::TEXTURE_RECTANGLE:
			type = GL_TEXTURE_RECTANGLE; break;

		case GraphicsAPI_DataType::PROXY_TEXTURE_RECTANGLE:
			type = GL_PROXY_TEXTURE_RECTANGLE; break;

		case GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_X:
			type = GL_TEXTURE_CUBE_MAP_POSITIVE_X; break;

		case GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_X:
			type = GL_TEXTURE_CUBE_MAP_NEGATIVE_X; break;

		case GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Y:
			type = GL_TEXTURE_CUBE_MAP_POSITIVE_Y; break;

		case GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Y:
			type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y; break;

		case GraphicsAPI_DataType::TEXTURE_CUBE_MAP_POSITIVE_Z:
			type = GL_TEXTURE_CUBE_MAP_POSITIVE_Z; break;

		case GraphicsAPI_DataType::TEXTURE_CUBE_MAP_NEGATIVE_Z:
			type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; break;

		case GraphicsAPI_DataType::PROXY_TEXTURE_CUBE_MAP:
			type = GL_PROXY_TEXTURE_CUBE_MAP; break;

		case GraphicsAPI_DataType::RED:
			type = GL_RED; break;

		case GraphicsAPI_DataType::RG:
			type = GL_RG; break;

		case GraphicsAPI_DataType::RGB:
			type = GL_RGB; break;

		case GraphicsAPI_DataType::BGR:
			type = GL_BGR; break;

		case GraphicsAPI_DataType::RGBA:
			type = GL_RGBA; break;

		case GraphicsAPI_DataType::BGRA:
			type = GL_BGRA; break;

		case GraphicsAPI_DataType::RED_INTEGER:
			type = GL_RED_INTEGER; break;

		case GraphicsAPI_DataType::RG_INTEGER:
			type = GL_RG_INTEGER; break;

		case GraphicsAPI_DataType::RGB_INTEGER:
			type = GL_RGB_INTEGER; break;

		case GraphicsAPI_DataType::BGR_INTEGER:
			type = GL_BGR_INTEGER; break;

		case GraphicsAPI_DataType::RGBA_INTEGER:
			type = GL_RGBA_INTEGER; break;

		case GraphicsAPI_DataType::BGRA_INTEGER:
			type = GL_BGRA_INTEGER; break;

		case GraphicsAPI_DataType::STENCIL_INDEX:
			type = GL_STENCIL_INDEX; break;

		case GraphicsAPI_DataType::DEPTH_STENCIL:
			type = GL_DEPTH_STENCIL; break;

		case GraphicsAPI_DataType::DEPTH_STENCIL_TEXTURE_MODE:
			type = GL_DEPTH_STENCIL_TEXTURE_MODE; break;

		case GraphicsAPI_DataType::TEXTURE_BASE_LEVEL:
			type = GL_TEXTURE_BASE_LEVEL; break;

		case GraphicsAPI_DataType::TEXTURE_COMPARE_FUNC:
			type = GL_TEXTURE_COMPARE_FUNC; break;

		case GraphicsAPI_DataType::TEXTURE_COMPARE_MODE:
			type = GL_TEXTURE_COMPARE_MODE; break;

		case GraphicsAPI_DataType::TEXTURE_LOD_BIAS:
			type = GL_TEXTURE_LOD_BIAS; break;

		case GraphicsAPI_DataType::TEXTURE_MIN_FILTER:
			type = GL_TEXTURE_MIN_FILTER; break;

		case GraphicsAPI_DataType::TEXTURE_MAG_FILTER:
			type = GL_TEXTURE_MAG_FILTER; break;

		case GraphicsAPI_DataType::TEXTURE_MIN_LOD:
			type = GL_TEXTURE_MIN_LOD; break;

		case GraphicsAPI_DataType::TEXTURE_MAX_LOD:
			type = GL_TEXTURE_MAX_LOD; break;

		case GraphicsAPI_DataType::TEXTURE_MAX_LEVEL:
			type = GL_TEXTURE_MAX_LEVEL; break;

		case GraphicsAPI_DataType::TEXTURE_SWIZZLE_R:
			type = GL_TEXTURE_SWIZZLE_R; break;

		case GraphicsAPI_DataType::TEXTURE_SWIZZLE_G:
			type = GL_TEXTURE_SWIZZLE_G; break;

		case GraphicsAPI_DataType::TEXTURE_SWIZZLE_B:
			type = GL_TEXTURE_SWIZZLE_B; break;

		case GraphicsAPI_DataType::TEXTURE_SWIZZLE_A:
			type = GL_TEXTURE_SWIZZLE_A; break;

		case GraphicsAPI_DataType::TEXTURE_WRAP_S:
			type = GL_TEXTURE_WRAP_S; break;

		case GraphicsAPI_DataType::TEXTURE_WRAP_T:
			type = GL_TEXTURE_WRAP_T; break;

		case GraphicsAPI_DataType::TEXTURE_WRAP_R:
			type = GL_TEXTURE_WRAP_R; break;

		case GraphicsAPI_DataType::CLAMP_TO_EDGE:
			type = GL_CLAMP_TO_EDGE; break;

		case GraphicsAPI_DataType::CLAMP_TO_BORDER:
			type = GL_CLAMP_TO_BORDER; break;

		case GraphicsAPI_DataType::MIRRORED_REPEAT:
			type = GL_MIRRORED_REPEAT; break;

		case GraphicsAPI_DataType::REPEAT:
			type = GL_REPEAT; break;

		case GraphicsAPI_DataType::MIRROR_CLAMP_TO_EDGE:
			type = GL_MIRROR_CLAMP_TO_EDGE; break;

		case GraphicsAPI_DataType::GREEN:
			type = GL_GREEN; break;

		case GraphicsAPI_DataType::BLUE:
			type = GL_BLUE; break;

		case GraphicsAPI_DataType::ZERO:
			type = GL_ZERO; break;

		case GraphicsAPI_DataType::ONE:
			type = GL_ONE; break;

		case GraphicsAPI_DataType::NEAREST:
			type = GL_NEAREST; break;

		case GraphicsAPI_DataType::LINEAR:
			type = GL_LINEAR; break;

		case GraphicsAPI_DataType::NEAREST_MIPMAP_NEAREST:
			type = GL_NEAREST_MIPMAP_NEAREST; break;

		case GraphicsAPI_DataType::LINEAR_MIPMAP_NEAREST:
			type = GL_LINEAR_MIPMAP_NEAREST; break;

		case GraphicsAPI_DataType::NEAREST_MIPMAP_LINEAR:
			type = GL_NEAREST_MIPMAP_LINEAR; break;

		case GraphicsAPI_DataType::LINEAR_MIPMAP_LINEAR:
			type = GL_LINEAR_MIPMAP_LINEAR; break;
		
		case GraphicsAPI_DataType::RGB16F:
			type = GL_RGB16F; break;

		case GraphicsAPI_DataType::RG16F:
			type = GL_RG16F; break;

		case GraphicsAPI_DataType::TEXTURE0:
			type = GL_TEXTURE0; break;

		case GraphicsAPI_DataType::TEXTURE_CUBE_MAP:
			type = GL_TEXTURE_CUBE_MAP; break;

		case GraphicsAPI_DataType::DRAW_FRAMEBUFFER:
			type = GL_DRAW_FRAMEBUFFER; break;

		case GraphicsAPI_DataType::READ_FRAMEBUFFER:
			type = GL_READ_FRAMEBUFFER; break;

		case GraphicsAPI_DataType::FRAMEBUFFER:
			type = GL_FRAMEBUFFER; break;

		case GraphicsAPI_DataType::RENDERBUFFER:
			type = GL_RENDERBUFFER; break;
			
		case GraphicsAPI_DataType::COLOR_ATTACHMENT0:
			type = GL_COLOR_ATTACHMENT0; break;

		case GraphicsAPI_DataType::DEPTH_ATTACHMENT:
			type = GL_DEPTH_ATTACHMENT; break;

		case GraphicsAPI_DataType::STENCIL_ATTACHMENT:
			type = GL_STENCIL_ATTACHMENT; break;

		case GraphicsAPI_DataType::ALPHA:
			type = GL_ALPHA; break;

		case GraphicsAPI_DataType::ALPHA4:
			type = GL_ALPHA4; break;

		case GraphicsAPI_DataType::ALPHA8:
			type = GL_ALPHA8; break;

		case GraphicsAPI_DataType::ALPHA12:
			type = GL_ALPHA12; break;

		case GraphicsAPI_DataType::ALPHA16:
			type = GL_ALPHA16; break;

		case GraphicsAPI_DataType::COMPRESSED_ALPHA:
			type = GL_COMPRESSED_ALPHA; break;

		case GraphicsAPI_DataType::COMPRESSED_LUMINANCE:
			type = GL_COMPRESSED_LUMINANCE; break;

		case GraphicsAPI_DataType::COMPRESSED_LUMINANCE_ALPHA:
			type = GL_COMPRESSED_LUMINANCE_ALPHA; break;

		case GraphicsAPI_DataType::COMPRESSED_INTENSITY:
			type = GL_COMPRESSED_INTENSITY; break;

		case GraphicsAPI_DataType::COMPRESSED_RGB:
			type = GL_COMPRESSED_RGB; break;

		case GraphicsAPI_DataType::COMPRESSED_RGBA:
			type = GL_COMPRESSED_RGBA; break;

		case GraphicsAPI_DataType::DEPTH_COMPONENT:
			type = GL_DEPTH_COMPONENT; break;

		case GraphicsAPI_DataType::DEPTH_COMPONENT16:
			type = GL_DEPTH_COMPONENT16; break;

		case GraphicsAPI_DataType::DEPTH_COMPONENT24:
			type = GL_DEPTH_COMPONENT24; break;

		case GraphicsAPI_DataType::DEPTH_COMPONENT32:
			type = GL_DEPTH_COMPONENT32; break;

		case GraphicsAPI_DataType::LUMINANCE:
			type = GL_LUMINANCE; break;

		case GraphicsAPI_DataType::LUMINANCE4:
			type = GL_LUMINANCE4; break;

		case GraphicsAPI_DataType::LUMINANCE8:
			type = GL_LUMINANCE8; break;

		case GraphicsAPI_DataType::LUMINANCE12:
			type = GL_LUMINANCE12; break;

		case GraphicsAPI_DataType::LUMINANCE16:
			type = GL_LUMINANCE16; break;

		case GraphicsAPI_DataType::LUMINANCE_ALPHA:
			type = GL_LUMINANCE_ALPHA; break;

		case GraphicsAPI_DataType::LUMINANCE4_ALPHA4:
			type = GL_LUMINANCE4_ALPHA4; break;

		case GraphicsAPI_DataType::LUMINANCE6_ALPHA2:
			type = GL_LUMINANCE6_ALPHA2; break;

		case GraphicsAPI_DataType::LUMINANCE8_ALPHA8:
			type = GL_LUMINANCE8_ALPHA8; break;

		case GraphicsAPI_DataType::LUMINANCE12_ALPHA4:
			type = GL_LUMINANCE12_ALPHA4; break;

		case GraphicsAPI_DataType::LUMINANCE12_ALPHA12:
			type = GL_LUMINANCE12_ALPHA12; break;

		case GraphicsAPI_DataType::LUMINANCE16_ALPHA16:
			type = GL_LUMINANCE16_ALPHA16; break;

		case GraphicsAPI_DataType::INTENSITY:
			type = GL_INTENSITY; break;

		case GraphicsAPI_DataType::INTENSITY4:
			type = GL_INTENSITY4; break;

		case GraphicsAPI_DataType::INTENSITY8:
			type = GL_INTENSITY8; break;

		case GraphicsAPI_DataType::INTENSITY12:
			type = GL_INTENSITY12; break;

		case GraphicsAPI_DataType::INTENSITY16:
			type = GL_INTENSITY16; break;

		case GraphicsAPI_DataType::R3_G3_B2:
			type = GL_R3_G3_B2; break;

		case GraphicsAPI_DataType::RGB4:
			type = GL_RGB4; break;

		case GraphicsAPI_DataType::RGB5:
			type = GL_RGB5; break;

		case GraphicsAPI_DataType::RGB8:
			type = GL_RGB8; break;

		case GraphicsAPI_DataType::RGB10:
			type = GL_RGB10; break;

		case GraphicsAPI_DataType::RGB12:
			type = GL_RGB12; break;

		case GraphicsAPI_DataType::RGB16:
			type = GL_RGB16; break;

		case GraphicsAPI_DataType::RGBA2:
			type = GL_RGBA2; break;

		case GraphicsAPI_DataType::RGBA4:
			type = GL_RGBA4; break;

		case GraphicsAPI_DataType::RGB5_A1:
			type = GL_RGB5_A1; break;

		case GraphicsAPI_DataType::RGBA8:
			type = GL_RGBA8; break;

		case GraphicsAPI_DataType::RGB10_A2:
			type = GL_RGB10_A2; break;

		case GraphicsAPI_DataType::RGBA12:
			type = GL_RGBA12; break;

		case GraphicsAPI_DataType::RGBA16:
			type = GL_RGBA16; break;

		case GraphicsAPI_DataType::SLUMINANCE:
			type = GL_SLUMINANCE; break;

		case GraphicsAPI_DataType::SLUMINANCE8:
			type = GL_SLUMINANCE8; break;

		case GraphicsAPI_DataType::SLUMINANCE_ALPHA:
			type = GL_SLUMINANCE_ALPHA; break;

		case GraphicsAPI_DataType::SLUMINANCE8_ALPHA8:
			type = GL_SLUMINANCE8_ALPHA8; break;

		case GraphicsAPI_DataType::SRGB:
			type = GL_SRGB; break;

		case GraphicsAPI_DataType::SRGB8:
			type = GL_SRGB8; break;

		case GraphicsAPI_DataType::SRGB_ALPHA:
			type = GL_SRGB_ALPHA; break;

		case GraphicsAPI_DataType::SRGB8_ALPHA8:
			type = GL_SRGB8_ALPHA8; break;


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


		default: 
			assert(false);
			break;
	}

	// check if fails
	assert (type != -2147483648);

	return type;
}

void GraphicsAPI_OpenGL::GenerateBuffers(unsigned int* _ids, int _length) const
{
	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml
	glGenBuffers(_length, _ids);
}

void GraphicsAPI_OpenGL::BindBuffer(GraphicsAPI_DataType _type, unsigned int _id) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_type));
	const GLuint buffer = static_cast<GLuint>(_id);
	
	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
	glBindBuffer(target, buffer);
}

void GraphicsAPI_OpenGL::UnbindBuffer(GraphicsAPI_DataType _type) const
{
	BindBuffer(_type, static_cast<unsigned int>(NULL));
}

void GraphicsAPI_OpenGL::SetBuffers(GraphicsAPI_DataType _type, size_t _size, const void *_data, GraphicsAPI_DataType _additionalType) const
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

void GraphicsAPI_OpenGL::EnableVertexArrayAttribute(unsigned int _VAOid) const
{
	const GLuint index = static_cast<GLuint>(_VAOid);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
	glEnableVertexAttribArray(index);
}

void GraphicsAPI_OpenGL::DisableVertexArrayAttribute(unsigned int _VAOid) const
{
	const GLuint index = static_cast<GLuint>(_VAOid);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
	glDisableVertexAttribArray(index);
}

void GraphicsAPI_OpenGL::SetVertexArray(unsigned int _VAOid, unsigned int _size, GraphicsAPI_DataType _type, GraphicsAPI_DataType _normalized, unsigned int _stride, const void* ptr) const
{
	const GLuint index = static_cast<GLuint>(_VAOid);
	const GLint size = static_cast<GLint>(_size);
	const GLenum type = static_cast<GLenum>(GetType(_type));
	const GLboolean normalized = static_cast<GLboolean>(GetType(_normalized));
	const GLsizei stride = static_cast<GLsizei>(_stride);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(index, size, type, normalized, stride, ptr);
}

void GraphicsAPI_OpenGL::BindVertexArray(unsigned int _id) const
{
	const GLuint array = static_cast<GLuint>(_id);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml
	glBindVertexArray(array);
}

void GraphicsAPI_OpenGL::UnbindVertexArray() const
{
	BindVertexArray(static_cast<unsigned int>(NULL));
}

void GraphicsAPI_OpenGL::GenerateVertexArrays(unsigned int* _ids, int _length) const
{
	const GLsizei n = static_cast<GLsizei>(_length);
	GLuint* arrays = static_cast<GLuint*> (_ids);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
	glGenVertexArrays(n, arrays);
}

void GraphicsAPI_OpenGL::SetupVAO(unsigned int* _VAO, Mesh* _mesh, GraphicsAPI_DataType _type) const
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
	SetBuffers(GraphicsAPI_DataType::ARRAY_BUFFER, vec3Size * _mesh->normal.size(), _mesh->normal.data(), _type);

	BindBuffer(GraphicsAPI_DataType::ARRAY_BUFFER, VBO[2]);
	SetBuffers(GraphicsAPI_DataType::ARRAY_BUFFER, vec2Size * _mesh->uv0.size(), _mesh->uv0.data(), _type);

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

unsigned int GraphicsAPI_OpenGL::CompileShader(std::string _vertexShaderSource, std::string _geometryShaderSource, std::string _fragmentShaderSouce) const
{
	auto ReadFile = [](const char* filename) -> char* {
		FILE *fp = fopen(filename, "rb");
		fseek(fp, 0, SEEK_END);
		long fsize = ftell(fp);
		fseek(fp, 0, SEEK_SET);  //same as rewind(fp);

		char* buffer = (char *)malloc(sizeof(char) * (fsize + 1));
		fread(buffer, fsize, 1, fp);
		fclose(fp);

		buffer[fsize] = 0;

		return buffer;
	};

	auto CreateShader_Impl = [](const char *source, const char *type) -> GLuint {
		
		GLuint shader;
		
		/* GLuint glCreateShader( GLenum shaderType ); */
		if (0 == strcmp(type, "vertex")) {			
			shader = glCreateShader(GL_VERTEX_SHADER);
		}
		else if (0 == strcmp(type, "fragment")) {
			shader = glCreateShader(GL_FRAGMENT_SHADER);
		}
		else if (0 == strcmp(type, "geometry")) {
			shader = glCreateShader(GL_GEOMETRY_SHADER);
		}
		else {
			puts("Error: Unknown type of shader.");
			return -1;
		}

		glShaderSource(shader, 1, (const GLchar **)&source, 0);

		glCompileShader(shader);
		GLint isCompiled = 0;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			char *infoLog = (char *)malloc(sizeof(char) * (maxLength));
			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

			//We don't need the shader anymore.
			glDeleteShader(shader);

			//Use the infoLog as you see fit.
			puts(infoLog);
			free(infoLog);

			//In this simple program, we'll just leave
			return -1;
		}

		return shader;
	};

	auto CreateShader = [&ReadFile, &CreateShader_Impl](const char *filename, const char *type) -> GLuint {
		char *source = ReadFile(filename);

		GLuint returnShader = CreateShader_Impl(source, type);

		// free allocated memory
		free(source);

		return returnShader;
	};

	auto CreateProgram = [](GLuint vert, GLuint frag, GLuint geom = -1) -> GLuint {
		
		GLuint program = glCreateProgram();

		//Attach our shaders to our program
		glAttachShader(program, vert);
		glAttachShader(program, frag);
		if (geom != -1) {
			glAttachShader(program, geom);
		}

		//Link our program
		glLinkProgram(program);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			char *infoLog = (char *)malloc(sizeof(char) * (maxLength));
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

			//We don't need the program anymore.
			glDeleteProgram(program);
			//Don't leak shaders either.
			glDeleteShader(vert);
			glDeleteShader(frag);

			//Use the infoLog as you see fit.
			puts(infoLog);
			free(infoLog);

			//In this simple program, we'll just leave
			return -1;
		}

		//Always detach shaders after a successful link.
		glDetachShader(program, vert);
		glDetachShader(program, frag);
		if (geom != -1) {
			glDetachShader(program, geom);
		}

		return program;
	};

	GLuint Vert = CreateShader(_vertexShaderSource.c_str(), "vertex");
	GLuint Geom = (_geometryShaderSource != "") ? CreateShader(_geometryShaderSource.c_str(), "geometry") : -1;
	GLuint Frag = CreateShader(_fragmentShaderSouce.c_str(), "fragment");	
	GLuint program = CreateProgram(Vert, Frag, Geom);

	return static_cast<unsigned int>(program);
}

void GraphicsAPI_OpenGL::BindProgram(unsigned int _program) const
{
	glUseProgram(_program);
}

void GraphicsAPI_OpenGL::UnbindProgram() const
{
	glUseProgram(static_cast<unsigned int>(NULL));
}

void GraphicsAPI_OpenGL::SetBool(unsigned int _program, const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(_program, name.c_str()), (int)value);
}

void GraphicsAPI_OpenGL::SetInt(unsigned int _program, const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
}

void GraphicsAPI_OpenGL::SetFloat(unsigned int _program, const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
}

void GraphicsAPI_OpenGL::SetVec2(unsigned int _program, const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
}
void GraphicsAPI_OpenGL::SetVec2(unsigned int _program, const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(_program, name.c_str()), x, y);
}

void GraphicsAPI_OpenGL::SetVec3(unsigned int _program, const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
}
void GraphicsAPI_OpenGL::SetVec3(unsigned int _program, const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(_program, name.c_str()), x, y, z);
}

void GraphicsAPI_OpenGL::SetVec4(unsigned int _program, const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
}

void GraphicsAPI_OpenGL::SetVec4(unsigned int _program, const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(_program, name.c_str()), x, y, z, w);
}

void GraphicsAPI_OpenGL::SetMat2(unsigned int _program, const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GraphicsAPI_OpenGL::SetMat3(unsigned int _program, const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GraphicsAPI_OpenGL::SetMat4(unsigned int _program, const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GraphicsAPI_OpenGL::ClearScreenColor() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsAPI_OpenGL::ClearScreenDepth() const
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsAPI_OpenGL::ClearScreenStencil() const
{
	glClear(GL_STENCIL_BUFFER_BIT);
}

int count = 0;

void GraphicsAPI_OpenGL::EnableDepthTest() const 
{
	count++;
	glEnable(GL_DEPTH_TEST);
}

void GraphicsAPI_OpenGL::DisableDepthTest() const 
{
	count--;
	glDisable(GL_DEPTH_TEST);
}

void GraphicsAPI_OpenGL::SetDepthMask(GraphicsAPI_DataType _type) const 
{
	const GLboolean flag = static_cast<GLboolean>(this->GetType(_type));

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glDepthMask.xml
	glDepthMask(flag);
}

void GraphicsAPI_OpenGL::SetDepthTestMode(GraphicsAPI_DataType _type) const 
{
	const GLenum func = static_cast<GLenum>(this->GetType(_type));

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glDepthFunc.xml
	glDepthFunc(func);
}

void GraphicsAPI_OpenGL::EnableStencilTest() const 
{
	glEnable(GL_STENCIL_TEST);
}

void GraphicsAPI_OpenGL::DisableStencilTest() const 
{
	glDisable(GL_STENCIL_TEST);
}

void GraphicsAPI_OpenGL::SetStencilMask(unsigned int _mask) const 
{
	const GLuint mask = static_cast<GLuint>(_mask);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glDepthMask.xml
	glStencilMask(mask);
}

void GraphicsAPI_OpenGL::EnableBlending() const 
{
	glEnable(GL_BLEND);
}

void GraphicsAPI_OpenGL::DisableBlending() const 
{
	glDisable(GL_BLEND);
}

void GraphicsAPI_OpenGL::SetBlendingMode(GraphicsAPI_DataType _type, GraphicsAPI_DataType _additionalType) const 
{
	const GLenum sfactor = static_cast<GLenum>(this->GetType(_type));
	const GLenum dfactor = static_cast<GLenum>(this->GetType(_additionalType));

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBlendFunc.xhtml
	glBlendFunc(sfactor, dfactor);
}

void GraphicsAPI_OpenGL::EnableCulling() const 
{
	glEnable(GL_CULL_FACE);
}

void GraphicsAPI_OpenGL::DisableCulling() const 
{
	glDisable(GL_CULL_FACE);
}

void GraphicsAPI_OpenGL::SetCullingMode(GraphicsAPI_DataType _type) const 
{
	const GLenum mode = static_cast<GLenum>(this->GetType(_type));

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCullFace.xhtml
	glCullFace(mode);
}

// Syntactic sugar: set first default to 0 
void GraphicsAPI_OpenGL::DrawArrays(GraphicsAPI_DataType _type, unsigned int _count, int _first) const
{
	const GLenum mode = static_cast<GLenum>(this->GetType(_type));
	const GLint first = static_cast<GLint>(_first);
	const GLsizei count = static_cast<GLsizei>(_count);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
	glDrawArrays(mode, first, count);
}

void GraphicsAPI_OpenGL::GenerateTextures(unsigned int* _ids, unsigned int _length) const
{
	const GLsizei n = static_cast<GLsizei>(_length);
	GLuint* textures = static_cast<GLuint*>(_ids);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenTextures.xhtml
	glGenTextures(n, textures);
}

void GraphicsAPI_OpenGL::BindTexture(GraphicsAPI_DataType _type, unsigned int _id) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_type));
	const GLuint texture = static_cast<GLuint>(_id);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindTexture.xhtml
	glBindTexture(target, texture);
}

void GraphicsAPI_OpenGL::SetTexture2D(GraphicsAPI_DataType _targetType, unsigned int _level, GraphicsAPI_DataType _channelType, unsigned int _width, unsigned int _height, int _border, GraphicsAPI_DataType _formatType, GraphicsAPI_DataType _type, const void* _data) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_targetType));
	const GLint level = static_cast<GLint>(_level);
	const GLint internalformat = static_cast<GLint>(this->GetType(_channelType));
	const GLsizei width = static_cast<GLsizei>(_width);
	const GLsizei height = static_cast<GLsizei>(_height);
	const GLint border = static_cast<GLint>(_border);
	const GLenum format = static_cast<GLenum>(this->GetType(_formatType));
	const GLenum type = static_cast<GLenum>(this->GetType(_type));

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
	glTexImage2D(target, level, internalformat, width, height, border, format, type, _data);
}

// map to glTextureParameteri For now
void GraphicsAPI_OpenGL::SetTextureParameter(GraphicsAPI_DataType _targetType, GraphicsAPI_DataType _pname, GraphicsAPI_DataType _param) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_targetType));
	const GLenum pname = static_cast<GLenum>(this->GetType(_pname));
	const GLfloat param = static_cast<GLfloat>(this->GetType(_param));

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
	glTexParameteri(target, pname, param);
}

void GraphicsAPI_OpenGL::ActiveTexture(unsigned int _texture) const
{
	const GLenum texture = static_cast<GLenum>(this->GetType(GraphicsAPI_DataType::TEXTURE0) + _texture);
	
	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glActiveTexture.xhtml
	glActiveTexture(texture);
}

void GraphicsAPI_OpenGL::EnableTexture2D() const
{
	glEnable(GL_TEXTURE_2D);
}

void GraphicsAPI_OpenGL::DisableTexture2D() const
{
	glDisable(GL_TEXTURE_2D);
}

void GraphicsAPI_OpenGL::UnbindTexture(GraphicsAPI_DataType _type) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_type));

	glBindTexture(target, static_cast<unsigned int>(NULL));
}

void GraphicsAPI_OpenGL::EnableSeamlessCubemap() const
{
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void GraphicsAPI_OpenGL::DisableSeamlessCubemap() const
{
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void GraphicsAPI_OpenGL::GenerateFrameBuffers(unsigned int* _ids, unsigned int _length) const
{
	const GLsizei n = static_cast<GLsizei>(_length);
	GLuint* ids = static_cast<GLuint*>(_ids);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenFramebuffers.xhtml
	glGenFramebuffers(n, ids);
}

void GraphicsAPI_OpenGL::BindFrameBuffer(GraphicsAPI_DataType _type, unsigned int _id) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_type));
	const GLuint framebuffer = static_cast<GLuint>(_id);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindFramebuffer.xhtml
	glBindFramebuffer(target, framebuffer);
}

void GraphicsAPI_OpenGL::UnbindFrameBuffer(GraphicsAPI_DataType _type) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_type));
	glBindFramebuffer(target, static_cast<unsigned int>(NULL));
}

void GraphicsAPI_OpenGL::AttachRenderBufferToFrameBuffer(GraphicsAPI_DataType _target, GraphicsAPI_DataType _attachment, GraphicsAPI_DataType _renderBufferTarget, unsigned int _renderBuffer) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_target));
	const GLenum attachment = static_cast<GLenum>(this->GetType(_attachment));
	const GLenum renderbuffertarget = static_cast<GLenum>(this->GetType(_renderBufferTarget));
	const GLuint renderbuffer = static_cast<GLuint>(_renderBuffer);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glFramebufferRenderbuffer.xml
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void GraphicsAPI_OpenGL::GenerateRenderBuffers(unsigned int* _ids, unsigned int _length) const
{
	const GLsizei n = static_cast<GLsizei>(_length);
	GLuint* renderbuffers = static_cast<GLuint*>(_ids);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glGenRenderbuffers.xml
	glGenRenderbuffers(n, renderbuffers);
}

void GraphicsAPI_OpenGL::BindRenderBuffer(GraphicsAPI_DataType _type, unsigned int _id) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_type));
	const GLuint renderbuffer = static_cast<GLuint>(_id);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glBindRenderbuffer.xml
	glBindRenderbuffer(target, renderbuffer);
}

void GraphicsAPI_OpenGL::UnbindRenderBuffer(GraphicsAPI_DataType _type) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_type));
	
	glBindRenderbuffer(target, static_cast<unsigned int>(NULL));
}

void GraphicsAPI_OpenGL::SetRenderBuffer(GraphicsAPI_DataType _target, GraphicsAPI_DataType _internalFormat, unsigned int _width, unsigned int _height) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_target));
	const GLenum internalformat = static_cast<GLenum>(this->GetType(_internalFormat));
	const GLsizei width = static_cast<GLsizei>(_width);
	const GLsizei height = static_cast<GLsizei>(_height);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glRenderbufferStorage.xhtml
	glRenderbufferStorage(target, internalformat, width, height);
}

void GraphicsAPI_OpenGL::SetFrameBuffer2D(GraphicsAPI_DataType _target, GraphicsAPI_DataType _attachment, GraphicsAPI_DataType _textarget, unsigned int _texture, int _level) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_target));
	const GLenum attachment = static_cast<GLenum>(this->GetType(_attachment));
	const GLenum textarget = static_cast<GLenum>(this->GetType(_textarget));
	const GLuint texture = static_cast<GLuint>(_texture);
	const GLint level = static_cast<GLint>(_level);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glFramebufferTexture2D.xml
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void GraphicsAPI_OpenGL::SetViewport(int _x, int _y, unsigned int _width, unsigned int _height) const
{
	const GLint x = static_cast<GLint>(_x);
	const GLint y = static_cast<GLint>(_y);
	const GLsizei width = static_cast<GLsizei>(_width);
	const GLsizei height = static_cast<GLsizei>(_height);

	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glViewport.xml
	glViewport(x, y, width, height);
}

void GraphicsAPI_OpenGL::GenerateMipmap(GraphicsAPI_DataType _target) const
{
	const GLenum target = static_cast<GLenum>(this->GetType(_target));
	
	// Reference: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenerateMipmap.xhtml
	glGenerateMipmap(target);
}