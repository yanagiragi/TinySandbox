#pragma once

#include "GraphicsAPI.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "MeshRenderer.hpp"
#include "EquirectangularToCubemapMaterial.hpp"

namespace TinySandbox
{
	class CubemapConverter : public MeshRenderer
	{
		public:

			CubemapConverter();

			static unsigned int Convert(Texture& _tex);

		private:

			static CubemapConverter* Instance();

			void InitializeFrameBufferObjects(GraphicsAPI* m_api);

			unsigned int m_frameBufferObject;
			unsigned int m_renderBufferObject;
			EquirectangularToCubemapMaterial* m_ConvertMaterial;

			static CubemapConverter* m_instance;
	};
}