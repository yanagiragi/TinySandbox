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

		// No these for now
		/*
			GL_UNSIGNED_BYTE_3_3_2,
			GL_UNSIGNED_BYTE_2_3_3_REV,
			GL_UNSIGNED_SHORT_5_6_5,
			GL_UNSIGNED_SHORT_5_6_5_REV,
			GL_UNSIGNED_SHORT_4_4_4_4,
			GL_UNSIGNED_SHORT_4_4_4_4_REV,
			GL_UNSIGNED_SHORT_5_5_5_1,
			GL_UNSIGNED_SHORT_1_5_5_5_REV,
			GL_UNSIGNED_INT_8_8_8_8,
			GL_UNSIGNED_INT_8_8_8_8_REV,
			GL_UNSIGNED_INT_10_10_10_2,
			GL_UNSIGNED_INT_2_10_10_10_REV,
		*/

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

		// FrameBuffers
		DRAW_FRAMEBUFFER,
		READ_FRAMEBUFFER,
		FRAMEBUFFER,
		RENDERBUFFER,

		// interal formats
		COLOR_ATTACHMENT0,
		DEPTH_ATTACHMENT,
		STENCIL_ATTACHMENT,
		ALPHA,
		ALPHA4,
		ALPHA8,
		ALPHA12,
		ALPHA16,
		COMPRESSED_ALPHA,
		COMPRESSED_LUMINANCE,
		COMPRESSED_LUMINANCE_ALPHA,
		COMPRESSED_INTENSITY,
		COMPRESSED_RGB,
		COMPRESSED_RGBA,
		DEPTH_COMPONENT,
		DEPTH_COMPONENT16,
		DEPTH_COMPONENT24,
		DEPTH_COMPONENT32,
		LUMINANCE,
		LUMINANCE4,
		LUMINANCE8,
		LUMINANCE12,
		LUMINANCE16,
		LUMINANCE_ALPHA,
		LUMINANCE4_ALPHA4,
		LUMINANCE6_ALPHA2,
		LUMINANCE8_ALPHA8,
		LUMINANCE12_ALPHA4,
		LUMINANCE12_ALPHA12,
		LUMINANCE16_ALPHA16,
		INTENSITY,
		INTENSITY4,
		INTENSITY8,
		INTENSITY12,
		INTENSITY16,
		R3_G3_B2,
		// RGB, // already appears
		RGB4,
		RGB5,
		RGB8,
		RGB10,
		RGB12,
		RGB16,
		// RGBA, // already appears
		RGBA2,
		RGBA4,
		RGB5_A1,
		RGBA8,
		RGB10_A2,
		RGBA12,
		RGBA16,
		SLUMINANCE,
		SLUMINANCE8,
		SLUMINANCE_ALPHA,
		SLUMINANCE8_ALPHA8,
		SRGB,
		SRGB8,
		SRGB_ALPHA,
		SRGB8_ALPHA8,

		// texture
		TEXTURE_2D,
		PROXY_TEXTURE_2D,
		TEXTURE_1D_ARRAY,
		PROXY_TEXTURE_1D_ARRAY,
		TEXTURE_RECTANGLE,
		PROXY_TEXTURE_RECTANGLE,
		TEXTURE_CUBE_MAP_POSITIVE_X,
		TEXTURE_CUBE_MAP_NEGATIVE_X,
		TEXTURE_CUBE_MAP_POSITIVE_Y,
		TEXTURE_CUBE_MAP_NEGATIVE_Y,
		TEXTURE_CUBE_MAP_POSITIVE_Z,
		TEXTURE_CUBE_MAP_NEGATIVE_Z,
		PROXY_TEXTURE_CUBE_MAP,
		TEXTURE0,
		TEXTURE_CUBE_MAP,

		// Pixel data format
		RED,
		RG,
		RGB,
		BGR,
		RGBA,
		BGRA,
		RED_INTEGER,
		RG_INTEGER,
		RGB_INTEGER,
		BGR_INTEGER,
		RGBA_INTEGER,
		BGRA_INTEGER,
		STENCIL_INDEX,
		DEPTH_STENCIL,
		RGB16F,

		// Texture Parameter
		DEPTH_STENCIL_TEXTURE_MODE,
		TEXTURE_BASE_LEVEL,
		TEXTURE_COMPARE_FUNC,
		TEXTURE_COMPARE_MODE,
		TEXTURE_LOD_BIAS,
		TEXTURE_MIN_FILTER,
		TEXTURE_MAG_FILTER,
		TEXTURE_MIN_LOD,
		TEXTURE_MAX_LOD,
		TEXTURE_MAX_LEVEL,
		TEXTURE_SWIZZLE_R,
		TEXTURE_SWIZZLE_G,
		TEXTURE_SWIZZLE_B,
		TEXTURE_SWIZZLE_A,
		TEXTURE_WRAP_S,
		TEXTURE_WRAP_T,
		TEXTURE_WRAP_R,

		// warp parameter
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER,
		MIRRORED_REPEAT,
		REPEAT,
		MIRROR_CLAMP_TO_EDGE,

		// swizzle parameter, RED already appears at Pixel data format
		GREEN,
		BLUE,
		// ALPHA, appears in internal format
		ZERO,
		ONE,

		// texture filter parameters
		NEAREST,
		LINEAR,
		NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR,

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
				GraphicsAPI::m_type = _api->GetAPIType();
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

			const GraphicsAPI_Type& GetAPIType() const {
				return m_type;
			}

			// virtual void Init();

			// define virtual functions
			// i.e., virtual void BindTextures(Texture, uint_32t);

			// Maps GraphicsAPI_DataType to actual MACRO type
			virtual float GetType(GraphicsAPI_DataType _type) const = 0;

			virtual void GenerateBuffers(unsigned int* _ids, int _length) const = 0;
			virtual void BindBuffer(GraphicsAPI_DataType _type, unsigned int _id) const = 0;
			virtual void UnbindBuffer(GraphicsAPI_DataType _type) const = 0;
			virtual void SetBuffers(
				GraphicsAPI_DataType _type, 
				size_t _size, 
				const void* _data, 
				GraphicsAPI_DataType _additionalType
			) const = 0;

			virtual void GenerateVertexArrays(unsigned int* _ids, int _length) const = 0;
			virtual void BindVertexArray(unsigned int _id) const = 0;
			virtual void UnbindVertexArray() const = 0;
			virtual void SetupVAO(unsigned int* _VAO, Mesh* _mesh, GraphicsAPI_DataType _type) const = 0;
			
			virtual void EnableVertexArrayAttribute(unsigned int _VAOid) const = 0;
			virtual void DisableVertexArrayAttribute(unsigned int _VAOid) const = 0;

			virtual void SetVertexArray(unsigned int _VAOid, unsigned int _size, GraphicsAPI_DataType _type, GraphicsAPI_DataType _normalized, unsigned int _stride, const void* ptr) const = 0;

			virtual unsigned int CompileShader(std::string _vertexShaderSource, std::string _geometryShaderSource, std::string _fragmentShaderSouce) const = 0;

			virtual void BindProgram(unsigned int _program) const = 0;
			virtual void UnbindProgram() const = 0;

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
			virtual void ClearScreenStencil() const = 0;

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

			virtual void GenerateTextures(unsigned int* _ids, unsigned int _length) const = 0;
			virtual void BindTexture(GraphicsAPI_DataType _type, unsigned int _id) const = 0;
			virtual void SetTexture2D(GraphicsAPI_DataType _targetType, unsigned int _level, GraphicsAPI_DataType _channelType, unsigned int width, unsigned int height, int border, GraphicsAPI_DataType _formatType, GraphicsAPI_DataType _type, const void* data) const = 0;
			virtual void SetTextureParameter(GraphicsAPI_DataType _targetType, GraphicsAPI_DataType _pname, GraphicsAPI_DataType _param) const = 0;
			virtual void ActiveTexture(unsigned int __texture) const = 0;
			virtual void EnableTexture2D() const = 0;
			virtual void DisableTexture2D() const = 0;
			virtual void UnbindTexture(GraphicsAPI_DataType _type) const = 0;

			virtual void EnableSeamlessCubemap() const = 0;
			virtual void DisableSeamlessCubemap() const = 0;

			virtual void GenerateFrameBuffers(unsigned int* _ids, unsigned int _length) const = 0;
			virtual void BindFrameBuffer(GraphicsAPI_DataType _type, unsigned int _id) const = 0;
			virtual void UnbindFrameBuffer(GraphicsAPI_DataType _type) const = 0;
			virtual void AttachRenderBufferToFrameBuffer(GraphicsAPI_DataType _target, GraphicsAPI_DataType _attachment, GraphicsAPI_DataType _renderBufferTarget, unsigned int _renderBuffer) const = 0;
			virtual void SetFrameBuffer2D(GraphicsAPI_DataType _target, GraphicsAPI_DataType _attachment, GraphicsAPI_DataType _textarget, unsigned int _texture, int _level) const = 0;

			virtual void GenerateRenderBuffers(unsigned int* _ids, unsigned int _length) const = 0;
			virtual void BindRenderBuffer(GraphicsAPI_DataType _type, unsigned int _id) const = 0;
			virtual void UnbindRenderBuffer(GraphicsAPI_DataType _type) const = 0;
			virtual void SetRenderBuffer(GraphicsAPI_DataType _target, GraphicsAPI_DataType _internalFormat, unsigned int _width, unsigned int _height) const = 0;

			virtual void SetViewport(int _x, int _y, unsigned int _width, unsigned int _height) const = 0;

			virtual void GenerateMipmap(GraphicsAPI_DataType _target) const = 0;

			// TODO:
			// glDrawBuffer(GL_NONE);
			// glReadBuffer(GL_NONE);

		private:
            static GraphicsAPI_Type m_type;
			static GraphicsAPI* m_api;
    };
}
