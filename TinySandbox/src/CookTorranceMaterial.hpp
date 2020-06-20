#pragma once

#include "BaseMaterial.hpp"
#include "Texture.hpp"
#include <glmathematics/glm.hpp>

namespace TinySandbox
{
	class CookTorranceMaterial : public BaseMaterial
	{
		public:
			CookTorranceMaterial();

			CookTorranceMaterial(Renderer* _renderer);

			CookTorranceMaterial(Renderer* _renderer, const char* _filename);

			void OnGUI() override;

			void Unuse() override;

			void Use() override;

			// TODO: Expose internel parameters

		private:
			Texture *m_cubemapTexture;
			float m_metallic, m_roughness, m_ambientOcculusion;
			glm::vec3 m_tint;
	};
}