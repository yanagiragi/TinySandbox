#pragma once

#include "MeshRenderer.hpp"
#include "Texture.hpp"

namespace TinySandbox
{
	class SkyboxRenderer : public MeshRenderer
	{
		public:

			SkyboxRenderer();

			~SkyboxRenderer();

			void OnRender() override;

			void SetTexture(Texture* _other);

		private:
			
	};
}