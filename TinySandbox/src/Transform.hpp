#pragma once

#include <glmathematics/glm.hpp>
#include <glmathematics/gtc/matrix_transform.hpp>
#include <glmathematics/gtc/type_ptr.hpp>


namespace TinySandbox
{
	class Transform
	{
		public:
			Transform()
			{
				m_position = glm::vec3(0.0, 0.0, 0.0);
				m_rotation = glm::vec3(0.0, 0.0, 0.0);
				m_scale = glm::vec3(1.0, 1.0, 1.0);
			}

			Transform(const Transform& _other)
			{
				m_position = _other.m_position;
				m_rotation = _other.m_rotation;
				m_scale = _other.m_scale;
			}
			
			Transform(const Transform* _other)
			{
				m_position = _other->m_position;
				m_rotation = _other->m_rotation;
				m_scale = _other->m_scale;
			}

			glm::mat4 toMatrix()
			{
				glm::mat4 model(1.0f);
				model = glm::scale(model, m_scale);
				model = glm::translate(model, m_position);
				model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
				model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
				model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
				return model; 
			}

			glm::vec3 Position() { return m_position; }
			glm::vec3 Rotation() { return m_rotation; }
			glm::vec3 Scale() { return m_scale; }

			void Position(const glm::vec3& _other) 
			{ 
				m_position = _other; 
			}
			
			void Rotation(const glm::vec3& _other)
			{ 
				m_rotation = _other; 

				auto Check = [](float &x) {
					if (x > 360.0f) {
						x -= 360.0f;
					}
					else if (x < 0.0f) {
						x += 360.0f;
					}
				};

				Check(m_rotation.x);
				Check(m_rotation.y);
				Check(m_rotation.z);				
			}
			
			void Scale(const glm::vec3& _other)
			{
				m_scale = _other;
			}

		private:
			glm::vec3 m_position;
			glm::vec3 m_scale;
			glm::vec3 m_rotation;
	};
}
