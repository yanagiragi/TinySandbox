#include "GraphicsAPI_OpenGL.hpp"

#include <assert.h>
#include <functional>

#include <glad/glad.h>

using namespace TinySandbox;

int GraphicsAPI_OpenGL::GetType(GraphicsAPI_DataType _dataType) const
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

unsigned int GraphicsAPI_OpenGL::CompileShader(std::string _vertexShaderSource, std::string _geometryShaderSource, std::string _fragmentShaderSouce)
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

void GraphicsAPI_OpenGL::BindProgram(unsigned int _program)
{
	glUseProgram(_program);
}

void GraphicsAPI_OpenGL::UnbindProgram()
{
	glUseProgram(NULL);
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

void GraphicsAPI_OpenGL::EnableDepthTest() const 
{
	glEnable(GL_DEPTH_TEST);
}

void GraphicsAPI_OpenGL::DisableDepthTest() const 
{
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