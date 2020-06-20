#pragma once

#include "Cubemap_BaseMaterial.hpp"
#include "Texture.hpp"

namespace TinySandbox
{
	class CubemapConvolveMaterial : public Cubemap_BaseMaterial
	{
		public:

			CubemapConvolveMaterial();

			CubemapConvolveMaterial(Renderer* _renderer);

			void OnGUI() override;

			void Use(int index) override;

			void Unuse() override;

	};
}
