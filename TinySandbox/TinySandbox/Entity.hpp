#pragma once

#include "Component.hpp"

#include <vector>

namespace TinySandbox
{
	class Entity : Component 
	{
		public:
			
			// ctor
			Entity() 
			{
			
			}
		
			// dtor
			~Entity()
			{
				components.clear();
			}

			// Copy constructor
			Entity(const Entity& other)
			{
				std::copy(std::begin(other.components), std::end(other.components), std::back_inserter(components));
			};

			// Move constructor
			Entity(Entity&& other)
			{
				std::move(std::begin(other.components), std::end(other.components), std::back_inserter(components));
			};

			// Assignment Operators
			Entity& operator= (const Entity& other) = delete;
			Entity& operator= (Entity&& other) = delete;

			void Start() override
			{
				for (auto component : components) {
					component->Start();
				}
			}

			void Update() override
			{
				for (auto component : components) {
					component->Update();
				}
			}

			void OnGUI() override
			{
				for (auto component : components) {
					component->OnGUI();
				}
			}

			// Only add is allowed, no other operation (e.g. delete) is provided.
			void Add(Component* _components)
			{
				components.push_back(_components);
			}

		 private:
			std::vector<Component*> components;
	};
}