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

	enum class CubemapTextureType
	{
		REGULAR,
		IRRADIANCE,
		PREFILTER,
		LEN
	};

	class Texture
	{
		public:

			friend class CubemapConverter;
			
			// Sometimes texture is loaded with external resources, e.g. create a texture to catch frame buffer
			Texture();
			Texture(const char* filename, TextureType _textureType, bool _isHDR, bool _isCubemap, int isPrefilter, int _cubemapResolution, int _convCubemapResolution, int _PrefiltercubemapResolution, int _mipsLevel);
			Texture(const char* filename, TextureType _textureType, bool _isHDR, bool _isCubemap, int _cubemapResolution);
			Texture(const char* filename, TextureType _textureType, bool _isHDR);
			Texture(const Texture& _other);		
			
			~Texture();
			
			void SetupTexture(GraphicsAPI_DataType _flag);

			unsigned int GetWidth() const { return m_width; }
			unsigned int GetHeight() const { return m_height; }
			unsigned int GetChannel() const { return m_channel; }
			unsigned int GetID() const { return m_textureId; }
			unsigned int GetID(CubemapTextureType _type) const { 
				if (isCubemap == false) {
					throw "Invalid call to GetID(CubemapTextureType _type), Only call this on cubemap!";
				}
				else if (_type == CubemapTextureType::REGULAR) {
					return m_textureId;
				}
				else if (_type == CubemapTextureType::IRRADIANCE) {
					return m_convTextureId;
				}
				else if (_type == CubemapTextureType::PREFILTER) {
					return m_prefilterTextureId;
				}
				else {
					throw "Invalid call to GetID(CubemapTextureType _type), Error argument!";
				}				
			}

			int GetMaxLod() const { return m_mipsLevel;  }

			bool isHighDynamicRange, isCubemap, isPrefiltered;
		
		private:
			
			unsigned int LoadTexture_STB(const char* name, int* width, int* height, int* components, GraphicsAPI_DataType _wrapFlag);
			unsigned int LoadHDRTexture_STB(const char* name, int* width, int* height, int* components, GraphicsAPI_DataType _wrapFlag);

			std::string m_filename;
			int m_width, m_height, m_channel;
			int m_cubemapResolution, m_convCubemapResolution, m_prefiltercubemapResolution, m_mipsLevel;
			unsigned int m_textureId, m_convTextureId, m_prefilterTextureId;
			TextureType m_textureType; // define it is a 2D/3D texture
			
			GraphicsAPI* m_api;
	};
}
