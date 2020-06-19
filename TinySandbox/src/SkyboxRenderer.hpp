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

		private:
			
	};
}