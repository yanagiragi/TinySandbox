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

			void Use() override;
			
			void Unuse() override;

			void SetLod(int _lod) { m_lod = _lod; }

			void SetMaxLod(int _maxLod) { m_maxLod = _maxLod; }

		private:
			int m_lod, m_maxLod;
	};
}
