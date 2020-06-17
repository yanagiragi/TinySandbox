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
		}

		~Renderer() {
			if (m_material) {
				delete m_material;
			}			
		}

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void OnGUI() = 0;
		virtual void OnRender() = 0;

		void SetMaterial(Material* _mat) { m_material = _mat; }
		Material* GetMaterial() const { return m_material; }

		protected:
			Material* m_material;
	};
}