#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include <vector>

namespace TinySandbox
{
	class Scene : public Component
	{
		public:
			
			Scene();

			Scene(const Scene& _scene) 
			{
				//std::copy(std::begin(other.entitiesList), std::end(other.entitiesList), std::back_inserter(entitiesList));
				entitiesList = _scene.entitiesList;
			};
		
			~Scene() 
			{
				for (auto entity : entitiesList)
				{
					delete entity;
				}
			}

			Scene& operator= (const Scene& _scene) = delete;
			Scene& operator= (const Scene&& _scene) = delete;
			
			void Start() override
			{
				for (auto entity : entitiesList) {
					entity->Start();
				}
			}

			void Update() override
			{
				for (auto entity : entitiesList) {
					entity->Update();
				}
			}

			void OnGUI() override
			{
				for (auto entity : entitiesList) {
					entity->OnGUI();
				}
			}

			void Add(Entity* _entity)
			{
				entitiesList.push_back(_entity);
			}

		private:
			std::vector<Entity*> entitiesList;
	};
}
