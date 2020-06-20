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

		glm::vec3 GetTint() const { return m_tint; }
		void SetTint(glm::vec3 _other) { m_tint = _other; }

		float GetMetallic() const { return m_metallic; }
		void SetMetallic(float _other) { m_metallic = _other; }

		float GetRoughness() const { return m_roughness; }
		void SetRoughness(float _other) { m_roughness = _other; }
		
		float GetAmbientOcculusionTint() const { return m_ambientOcculusion; }
		void SetAmbientOcculusion(float _other) { m_ambientOcculusion = _other; }

		private:
			Texture *m_cubemapTexture;
			float m_metallic, m_roughness, m_ambientOcculusion;
			glm::vec3 m_tint;
	};
}