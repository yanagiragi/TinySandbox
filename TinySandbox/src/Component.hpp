#pragma once

// use Forward Declaration to avoid Circular Dependency
// Reference: https://stackoverflow.com/questions/7665912/double-include-solution
namespace TinySandbox {
	class Entity;
}

namespace TinySandbox
{
	class Component 
	{
		public:

			Component() : entity(nullptr) {

			}

			virtual void Start() = 0;
			virtual void Update() = 0;
			virtual void OnGUI() = 0;

			virtual void OnRender() {} // not force override

			virtual void SetEntity(Entity* _entity) {
				entity = _entity;
			}

			Entity* entity; // two-way binding
	};
}