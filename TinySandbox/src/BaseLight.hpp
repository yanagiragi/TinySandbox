#pragma once

#include "Component.hpp"

#include <glmathematics/glm.hpp>

namespace TinySandbox
{
	enum class Light_Type
	{
		DIRECTIONAL,
		POINT,
		SPOTLIGHT, // not implementated yet
		LEN
	};

	class BaseLight : public Component
	{
		public:
			BaseLight() {
				m_intensity = 1.0f;
				m_color = glm::vec3(1.0, 1.0, 1.0);
				m_position = glm::vec3(0, 0, 0);
				m_rotation = glm::vec3(0, 0, 0);
			}

			virtual float GetIntensity() const {
				return m_intensity;
			}

			virtual glm::vec3 GetRotation() const {
				return m_rotation;
			}

			virtual glm::vec3 GetPosition() const {
				return m_position;
			}

			virtual glm::vec3 GetColor() const {
				return m_color;
			}

		protected:
			float m_intensity;
			glm::vec3 m_color;
			glm::vec3 m_rotation;
			glm::vec3 m_position;
	};
}
