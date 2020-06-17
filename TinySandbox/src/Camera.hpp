#pragma once

#include <glmathematics/glm.hpp>
#include <glmathematics/gtc/matrix_transform.hpp>

namespace TinySandbox
{
	class Camera
	{
		public:
			
			Camera() = default;
			~Camera() = default;

			void Theta(const float &val) { m_theta = val; }
			const float Theta() const { return m_theta; }
			
			void Phi(const float &val) { m_phi = val; }
			const float Phi() const { return m_phi;  }
			
			void Position(const glm::vec3 &val) { m_position = val; }
			const glm::vec3 Position() const { return m_position;  }

			const glm::vec3 Forward() const { 
				
				auto thetaDeg = glm::radians(m_theta);
				auto phiDeg = glm::radians(m_phi);
				
				return glm::vec3(
					m_position.x + cos(thetaDeg) * cos(phiDeg),
					m_position.y + sin(thetaDeg),
					m_position.z - cos(thetaDeg) * sin(phiDeg)
				);
			}
			
			const glm::vec3 Up() const {
				return glm::vec3(0.0, 1.0, 0.0);
			}
			
			void NearPlaneDistance(const float &val) { m_nearPlaneDistance = val;  }
			const float NearPlaneDistance() const { return m_nearPlaneDistance; }

			void FarPlaneDistance(const float &val) { m_farPlaneDistance = val; }
			const float FarPlaneDistance() const { return m_farPlaneDistance;  }

			void FieldOfView(const float &val) { m_fieldOfView = val; }
			const float FieldOfView() const { return m_fieldOfView;  }

			void Aspect(const float &val) { m_aspect = val; }
			const float Aspect() const { return m_aspect; }

			const glm::mat4 ViewMatrix() const  {

				const float M_PI = 3.14f;

				//const glm::vec3 forward = glm::vec3(0, 0, 11);
				const glm::vec3 forward = Forward();
				glm::mat4 ViewMatrixLH = glm::lookAtLH(
					m_position,
					forward,
					glm::vec3(0.0, 1.0, 0.0));
				glm::mat4 ViewMatrixRH = glm::lookAtRH(
					m_position,
					forward,
					glm::vec3(0.0, 1.0, 0.0));

				return glm::lookAt(Position(), forward, Up());
			}

			const glm::mat4 ProjectionMatrix() const {
				return glm::perspective(
					glm::radians(m_fieldOfView),
					m_aspect,
					m_nearPlaneDistance,
					m_farPlaneDistance
				);
			}

		private:
			glm::vec3 m_position;
			float m_theta, m_phi; // degrees of m_forward in spherical coordinates
			
			float m_nearPlaneDistance, m_farPlaneDistance;
			float m_fieldOfView; // degrees
			float m_aspect;
	};
}
