#pragma once

#include "GraphicsAPI.hpp"
#include "Texture.hpp"
#include "Cubemap_BaseMaterial.hpp"

#include "MeshRenderer.hpp"
#include "EquirectangularToCubemapMaterial.hpp"
#include "CubemapConvolveMaterial.hpp"
#include "CubemapPrefilterMaterial.hpp"

namespace TinySandbox
{
	class CubemapConverter : public MeshRenderer
	{
		public:

			CubemapConverter();
			~CubemapConverter();

			static void ConvertToCubemapAndFilter(Texture& _tex);

			static unsigned int ConvertEquirectangularToCubemap(Texture& _tex);
			static unsigned int ConvertCubemapToConvolutedCubemap(Texture& _tex);
			static unsigned int ConvertCubemapToPrefilteredCubemap(Texture& _tex);

			static void SetupFrameBufferAndRenderBuffer(unsigned int _resolution);
			
			// assign source texture to check if source is hdr image
			static void SetupCubemapTexture(unsigned int& _target, unsigned int _resolution, bool isHDR);

		private:

			static void BiltCubemap(unsigned int _targetTextureId, Cubemap_BaseMaterial* _material, unsigned int _resolution);

			static CubemapConverter* Instance();

			void InitializeFrameBufferObjects(GraphicsAPI* m_api);

			unsigned int m_frameBufferObject;
			unsigned int m_renderBufferObject;
			EquirectangularToCubemapMaterial* m_convertMaterial;
			CubemapConvolveMaterial* m_convoluteMaterial;
			CubemapPrefilterMaterial* m_prefilterMaterial;

			static CubemapConverter* m_instance;
	};
}