#pragma once

#include "Material.hpp"

namespace TinySandbox
{
	class Scene;
	class Texture;
}

namespace TinySandbox
{
	class SkyboxMaterial : public Material
	{
		public:
			SkyboxMaterial(Renderer* _renderer);

			SkyboxMaterial(Renderer* _renderer, const char* _filename, bool _isHDR);

			SkyboxMaterial& operator=(const SkyboxMaterial& _other);

			void OnGUI() override;

			void Unuse() override;

			void Use() override;

			void SetMainTexture(Texture* _other);

		private:
			Texture* m_mainTexture;
	};
}
