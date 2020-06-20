#pragma once

#include "Component.hpp"
#include "GraphicsAPI.hpp"

namespace TinySandbox
{
	class BaseMaterial;

	class Renderer : public Component
	{
		public:

			Renderer();

			~Renderer();

			// child class should override functions in Components
			virtual void Start() override = 0;
			virtual void Update() override = 0;
			virtual void OnGUI() override = 0;
			virtual void OnRender() override = 0;

			void SetMaterial(BaseMaterial* _mat);

			BaseMaterial* GetMaterial() const { return m_material; }

			protected:
				BaseMaterial* m_material;
				GraphicsAPI* m_api;
	};
}