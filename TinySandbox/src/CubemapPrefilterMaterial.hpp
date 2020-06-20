#pragma once

#include "Cubemap_BaseMaterial.hpp"

namespace TinySandbox
{
	class CubemapPrefilterMaterial : public Cubemap_BaseMaterial
	{
		public:
			CubemapPrefilterMaterial();

			CubemapPrefilterMaterial(Renderer* _renderer);

			void OnGUI() override;

			void Use(int _index) override
			{
				Use(_index, 1, 1);
			}

			void Use(int _index, int _lod, int _maxLod);

			void Unuse() override;
	};
}
