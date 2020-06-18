#pragma once

#include "Component.hpp"
//#include "Material.hpp"

namespace TinySandbox
{
	class Material;

	class Renderer : public Component
	{
		public:

		Renderer() {
			m_material = nullptr;
			m_api = GraphicsAPI::GetAPI();
		}

		~Renderer() {
			if (m_material) {
				delete m_material;
			}			
		}

		// child class should override functions in Components
		virtual void Start() override = 0;
		virtual void Update() override = 0;
		virtual void OnGUI() override = 0;
		virtual void OnRender() override = 0;

		void SetMaterial(Material* _mat) { m_material = _mat; }
		Material* GetMaterial() const { return m_material; }

		protected:
			Material* m_material;
			GraphicsAPI* m_api;
	};
}