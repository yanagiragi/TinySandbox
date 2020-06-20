#pragma once

#include "MeshRenderer.hpp"
#include "Texture.hpp"
#include "SkyboxMaterial.hpp"

namespace TinySandbox
{
	class SkyboxRenderer : public MeshRenderer
	{
		public:

			SkyboxRenderer();

			~SkyboxRenderer();

			void OnRender() override;

			void SetTexture(Texture* _other);

			// helper function
			void SetDisplayMode(Skybox_DisplayType _mode);

			float GetLod() const { return dynamic_cast<SkyboxMaterial*>(m_material)->m_lod; }
			
			void SetLod(const float _lod) {
				
				// maxLod = 5 means range = [0, 4]
				const float maxLod = dynamic_cast<SkyboxMaterial*>(m_material)->GetMainTexture()->GetMaxLod() - 1.0;

				const float lod = (_lod < 0) ? 0.0 : ((_lod > maxLod) ? maxLod : _lod);
				
				dynamic_cast<SkyboxMaterial*>(m_material)->m_lod = lod;
				
			}

		private:
			
	};
}