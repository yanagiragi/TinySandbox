#pragma once

#include "Cubemap_BaseMaterial.hpp"
#include "Texture.hpp"

namespace TinySandbox
{
	class CubemapIrradianceConvolutionMaterial : public Cubemap_BaseMaterial
	{
		public:

			CubemapIrradianceConvolutionMaterial() = delete;

			CubemapIrradianceConvolutionMaterial(Renderer* _renderer);

			void OnGUI() override;

			void Use(int index) override;

			void Unuse() override;

	};
}
