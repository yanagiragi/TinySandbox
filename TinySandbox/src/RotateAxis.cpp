#include "RotateAxis.hpp"

#include "Entity.hpp"
#include "BaseLight.hpp"

#include <iostream>

namespace TinySandbox
{
	void RotateAxis::Start()
	{
		m_incrementAngle = 2.5;
	}

	void RotateAxis::Update()
	{
		Transform* transform = entity->GetTransform();

		glm::vec3 newRotation = transform->Rotation() + glm::vec3(0, m_incrementAngle, 0);

		newRotation.x = 0;
		newRotation.z = 180;

		transform->Rotation(newRotation);
	}

	void RotateAxis::OnGUI()
	{

	}
}