#pragma once

#include "GraphicsAPI.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
	#include <stb_image.h>
#endif // !STB_IMAGE_IMPLEMENTATION

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
	#define STB_IMAGE_WRITE_IMPLEMENTATION
	#include <stb_image_write.h>
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>

namespace TinySandbox
{
	enum class TextureType
	{
		TEXTURE_2D,
		TEXTURE_3D,
		LEN
	};

	class Texture
	{
		public:
			Texture(const char* filename, TextureType _textureType = TextureType::TEXTURE_2D, bool _isHDR = false)  : m_filename(filename)
			{
				m_textureType = _textureType;
				m_api = GraphicsAPI::GetAPI();
				isHighDyanmicRange = _isHDR;

				this->SetupTexture(GraphicsAPI_DataType::REPEAT);
			}

			Texture(const Texture& _other) : m_filename(_other.m_filename)
			{
				m_textureType = _other.m_textureType;
				isHighDyanmicRange = _other.isHighDyanmicRange;
				m_api = _other.m_api;
			}
			
			// Sometimes texture is loaded with external resources, e.g. create a texture to catch frame buffer
			Texture() 
			{
				m_filename = nullptr;
				m_textureType = TextureType::LEN;
				m_api = GraphicsAPI::GetAPI();
				isHighDyanmicRange = false;
			}

			~Texture()
			{
				if (m_filename) {
					free((char*)m_filename);
				}
			}

			unsigned int GetID()
			{
				return m_textureId;
			}

			void SetupTexture(GraphicsAPI_DataType _flag)
			{
				if (isHighDyanmicRange) {
					m_textureId = LoadHDRTexture_STB(m_filename, &m_width, &m_height, &m_channel, _flag);
				}
				else {
					m_textureId = LoadTexture_STB(m_filename, &m_width, &m_height, &m_channel, _flag);
				}
			}

			int GetWidth() const { return m_width; }
			int GetHeight() const { return m_height; }
			int GetChannel() const { return m_channel; }

			bool isHighDyanmicRange;
		
		private:
			unsigned int LoadTexture_STB(const char* name, int* width, int* height, int* components, GraphicsAPI_DataType _wrapFlag)
			{
				m_textureType = TextureType::TEXTURE_2D;

				stbi_set_flip_vertically_on_load(true);
				unsigned char *data = stbi_load(name, width, height, components, 0);

				unsigned int textureID = -1;
				
				if (data) {
					m_api->ActiveTexture(0);
					m_api->GenerateTextures(&textureID, 1);
					m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_2D, textureID);

					if (*components == 4) {
						m_api->SetTexture2D(
							GraphicsAPI_DataType::TEXTURE_2D,
							0, // lod level = 0
							GraphicsAPI_DataType::RGBA, // internal format, since we have 4 components, each for 8 bytes
							*width, *height, 0, // no border
							GraphicsAPI_DataType::RGBA, // type
							GraphicsAPI_DataType::UNSIGNED_BYTE,
							data
						);
					}
					else { // components = 3

						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *width, *height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

						/*m_api->SetTexture2D(
							GraphicsAPI_DataType::TEXTURE_2D,
							0, // lod level = 0
							GraphicsAPI_DataType::RGB, // internal format, since we have 4 components, each for 8 bytes
							*width, *height, 0, // no border
							GraphicsAPI_DataType::RGB, // type
							GraphicsAPI_DataType::UNSIGNED_BYTE,
							data
						);*/
					}

					m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_WRAP_S, _wrapFlag);
					m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_WRAP_T, _wrapFlag);

					m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_MIN_FILTER, GraphicsAPI_DataType::LINEAR);
					m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_MAG_FILTER, GraphicsAPI_DataType::LINEAR);

					m_api->UnbindTexture2D();

					stbi_image_free(data);
				}
				else {
					std::cout << "Failed to load image, " << stbi_failure_reason() << std::endl;
				}

				return textureID;
			}
			
			unsigned int LoadHDRTexture_STB(const char* name, int* width, int* height, int* components, GraphicsAPI_DataType _wrapFlag)
			{
				m_textureType = TextureType::TEXTURE_3D;

				stbi_set_flip_vertically_on_load(true);
				
				float *data = stbi_loadf(name, width, height, components, 0);

				unsigned int textureID = -1;
				if (data) {
					m_api->GenerateTextures(&textureID, 1);
					m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_2D, textureID);

					// note how we specify the texture's data value to be float
					m_api->SetTexture2D(
						GraphicsAPI_DataType::TEXTURE_2D,
						0, // lod level = 0
						GraphicsAPI_DataType::RGB16F, // internal format, since we have 4 components, each for 16 bytes
						*width, *height, 0, // no border
						GraphicsAPI_DataType::RGB, // type
						GraphicsAPI_DataType::FLOAT,
						data
					);

					m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_WRAP_S, _wrapFlag);
					m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_WRAP_T, _wrapFlag);

					m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_MIN_FILTER, GraphicsAPI_DataType::LINEAR);
					m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_MAG_FILTER, GraphicsAPI_DataType::LINEAR);

					stbi_image_free(data);
				}
				else {
					std::cout << "Failed to load HDR image, " << stbi_is_hdr(name) << ", " << stbi_failure_reason() << std::endl;
				}

				return textureID;
			}

			const char* m_filename;
			int m_width, m_height, m_channel;
			unsigned int m_textureId;
			TextureType m_textureType; // define it is a 2D/3D texture
			
			GraphicsAPI* m_api;
	};
}
