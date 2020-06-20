#pragma once

#include "BaseMaterial.hpp"

namespace TinySandbox
{
	class Scene;
	class Texture;
}

namespace TinySandbox
{
	enum class Skybox_DisplayType
	{
		REGULAR,
		IRRADIANCE,
		PREFILTER,
		LEN
	};

	class SkyboxMaterial : public BaseMaterial
	{
		friend class SkyboxRenderer;

		public:
			SkyboxMaterial(Renderer* _renderer);

			SkyboxMaterial(Renderer* _renderer, const char* _filename, bool _isHDR);

			SkyboxMaterial& operator=(const SkyboxMaterial& _other);

			void OnGUI() override;

			void Unuse() override;

			void Use() override;			

		private:
			Skybox_DisplayType m_mode;
			float m_lod; // for debug
	};
}
