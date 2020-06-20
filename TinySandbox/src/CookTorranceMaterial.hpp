#pragma once

#include "BaseMaterial.hpp"
#include "Texture.hpp"
#include <glmathematics/glm.hpp>

namespace TinySandbox
{
	class CookTorranceMaterial : public BaseMaterial
	{
		public:
			CookTorranceMaterial(Renderer* _renderer);

			void OnGUI() override;

			void Unuse() override;

			void Use() override;

		private:
			Texture* m_cubemapTexture, m_brdfTexture;
			float m_metallic, m_roughness, m_ambientOcculusion;
			glm::vec3 m_tint;
	};
}