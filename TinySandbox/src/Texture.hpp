#pragma once

#include "GraphicsAPI.hpp"

#include <string>

namespace TinySandbox
{
	enum class TextureType
	{
		TEXTURE_2D,
		CUBEMAP,
		TEXTURE_3D,
		LEN
	};

	class Texture
	{
		public:
			
			// Sometimes texture is loaded with external resources, e.g. create a texture to catch frame buffer
			Texture();
			Texture(const char* filename, TextureType _textureType, bool _isHDR, bool _isCubemap, int _cubemapResolution);
			Texture(const char* filename, TextureType _textureType, bool _isHDR);
			Texture(const Texture& _other);		
			
			~Texture();
			
			void SetupTexture(GraphicsAPI_DataType _flag);

			unsigned int GetWidth() const { return m_width; }
			unsigned int GetHeight() const { return m_height; }
			unsigned int GetChannel() const { return m_channel; }
			unsigned int GetCubemapResolution() const { return m_cubemapResolution; }
			unsigned int GetID() const { return m_textureId; }

			bool isHighDynamicRange, isCubemap;
		
		private:
			unsigned int LoadTexture_STB(const char* name, int* width, int* height, int* components, GraphicsAPI_DataType _wrapFlag);
			unsigned int LoadHDRTexture_STB(const char* name, int* width, int* height, int* components, GraphicsAPI_DataType _wrapFlag);

			std::string m_filename;
			int m_width, m_height, m_channel;
			int m_cubemapResolution;
			unsigned int m_textureId;
			TextureType m_textureType; // define it is a 2D/3D texture
			
			GraphicsAPI* m_api;
	};
}
