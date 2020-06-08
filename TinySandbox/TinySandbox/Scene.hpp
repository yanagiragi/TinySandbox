#pragma once

#include "includes/glad/glad.h"

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
				if (Scene::Instance() != nullptr) {
					for (auto entity : Scene::Instance()->entitiesList)
					{
						delete entity;
					}
				}
			}

			Scene& operator= (const Scene& _scene) = delete;
			Scene& operator= (const Scene&& _scene) = delete;

			void Start() override
			{
				for (auto entity : Scene::Instance()->entitiesList) {
					entity->Start();
				}
			}

			void Update() override
			{
				for (auto entity : Scene::Instance()->entitiesList) {
					entity->Update();
				}
			}

			void OnGUI() override
			{
				for (auto entity : Scene::Instance()->entitiesList) {
					entity->OnGUI();
				}
			}

			void Add(Entity* _entity)
			{
				Scene::Instance()->entitiesList.push_back(_entity);
			}

			static Scene* Instance()
			{
				if (Scene::m_instance == nullptr)
				{
					Scene::m_instance = new Scene();
				}
				return m_instance;
			}

			void InitSceneSettings();
			static void Draw();
			// static void ProcessInput(GLFWwindow* w) {} ;

		private:
			std::vector<Entity*> entitiesList;
			static Scene* m_instance; // singleton instance
	};
}
