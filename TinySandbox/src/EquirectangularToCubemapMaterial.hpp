#pragma once

#include "Cubemap_BaseMaterial.hpp"
#include "Texture.hpp"

namespace TinySandbox
{
	class EquirectangularToCubemapMaterial : public Cubemap_BaseMaterial
	{
		public:

			EquirectangularToCubemapMaterial();

			EquirectangularToCubemapMaterial(Renderer* _renderer);

			void OnGUI() override;

			void Unuse() override;

			void Use() override;
	};
}
