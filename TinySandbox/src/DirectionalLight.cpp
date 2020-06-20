#include "DirectionalLight.hpp"

#include "Entity.hpp"

namespace TinySandbox
{
	DirectionalLight::DirectionalLight() : BaseLight()
	{
		m_rotation = glm::vec3(0, 0, 0);
	}

	DirectionalLight::DirectionalLight(float _intensity, glm::vec3 _color) : BaseLight()
	{
		m_rotation = glm::vec3(0, 0, 1);
		m_intensity = _intensity;
		m_color = _color;
	}

	DirectionalLight::~DirectionalLight()
	{

	}

	void DirectionalLight::Start() {} // do nothing
	void DirectionalLight::Update() {} // do nothing

	void DirectionalLight::OnGUI()
	{

	}

	glm::vec3 DirectionalLight::GetRotation() const
	{
		// return m_rotation;
		return entity->GetTransform()->Rotation();
	}
}
