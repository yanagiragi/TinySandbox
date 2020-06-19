#pragma once

#include "Cubemap_BaseMaterial.hpp"
#include "Texture.hpp"

namespace TinySandbox
{
	class CubemapConvolveMaterial : public Cubemap_BaseMaterial
	{
		public:

			CubemapConvolveMaterial() = delete;

			CubemapConvolveMaterial(Renderer* _renderer);

			void OnGUI() override;

			void Use(int index) override;

			void Unuse() override;

	};
}
