#pragma once

#include "GraphicsAPI.hpp"
#include "Texture.hpp"

namespace TinySandbox
{
	class CubemapConverter
	{
		public:

			CubemapConverter();

			static void Convert(Texture& _tex);

		private:

			static void InitializeFrameBufferObjects(GraphicsAPI* m_api);

			static unsigned int m_frameBufferObject;
			static unsigned int m_renderBufferObject;
	};
}