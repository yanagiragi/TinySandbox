#pragma once

#include "Material.hpp"
#include "Texture.hpp"

namespace TinySandbox
{
	class EquirectangularToCubemapMaterial : public Material
	{
		public:

			EquirectangularToCubemapMaterial() = delete;

			EquirectangularToCubemapMaterial(Renderer* _renderer);

			void OnGUI() override;

			void Unuse() override;

			void Use() override {
				throw "Use Use(index) instead!";
			}

			void Use(int index);

			void SetMainTexture(Texture* _other);
		
		private:
			Texture* m_mainTexture;
			const glm::mat4 captureProjection;
			const glm::mat4 captureViews[6];
	};
}
