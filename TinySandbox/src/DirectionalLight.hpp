#pragma once

#include "BaseLight.hpp"


namespace TinySandbox
{
	class DirectionalLight : public BaseLight
	{
		public:
			DirectionalLight();

			DirectionalLight(float _intensity, glm::vec3 _color);

			~DirectionalLight();

			void Start() override;

			void Update() override;

			void OnGUI() override;

			glm::vec3 GetRotation() const override;
	};
}
