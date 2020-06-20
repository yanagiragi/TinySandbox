#include "Renderer.hpp"

#include "BaseMaterial.hpp"

namespace TinySandbox
{
	Renderer::Renderer() {
		m_material = nullptr;
		m_api = GraphicsAPI::GetAPI();
	}

	Renderer::~Renderer() {
		if (m_material) {
			delete m_material;
		}
	}

	void Renderer::SetMaterial(BaseMaterial* _mat) {
		m_material = _mat;
		m_material->SetRenderer(this);
	}
}