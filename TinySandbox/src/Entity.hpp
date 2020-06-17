#pragma once

//#include "Component.hpp"
#include "Transform.hpp"

#include <vector>

// use Forward Declaration to avoid Circular Dependency
// Reference: https://stackoverflow.com/questions/7665912/double-include-solution
namespace TinySandbox {
	class Component;
}

namespace TinySandbox
{
	class Entity : public Component 
	{
		public:
			
			// ctor
			Entity(const char* _name) : m_name(_name)
			{
				m_transform = new Transform();
			}
		
			// dtor
			~Entity()
			{
				if (m_transform) {
					delete m_transform;
				}

				for (auto component : m_components) {
					delete component;
				}
				m_components.clear();
			}

			// Copy constructor
			Entity(const Entity& other)
			{
				std::copy(std::begin(other.m_components), std::end(other.m_components), std::back_inserter(m_components));
				m_transform = new Transform(other.m_transform);
			};

			// Move constructor
			Entity(Entity&& other)
			{
				std::move(std::begin(other.m_components), std::end(other.m_components), std::back_inserter(m_components));
				m_transform = other.m_transform;
				other.m_transform = nullptr;
			};

			// Assignment Operators
			Entity& operator= (const Entity& other) = delete;
			Entity& operator= (Entity&& other) = delete;

			void Start() override
			{
				for (auto component : m_components) {
					component->Start();
				}
			}

			void Update() override
			{
				for (auto component : m_components) {
					component->Update();
				}
			}

			void OnGUI() override
			{
				for (auto component : m_components) {
					component->OnGUI();
				}
			}

			void OnRender() override
			{
				for (auto component : m_components) {
					component->OnRender();
				}
			}

			// Only add is allowed, no other operation (e.g. delete) is provided.
			void Add(Component* _components)
			{
				m_components.push_back(_components);
				_components->SetEntity(this); // bind this to component
			}

			Transform* GetTransform() const
			{
				return m_transform;
			}

		 private:
			const char* m_name;
			std::vector<Component*> m_components;
			Transform* m_transform;
	};
}