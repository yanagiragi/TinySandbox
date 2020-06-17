#pragma once

#include <glad/glad.h>

#include "Component.hpp"
#include "Entity.hpp"
#include "Camera.hpp"

#include <vector>

namespace TinySandbox
{
	class Scene : public Component
	{
		public:
			
			Scene();

			/*Scene(const Scene& _scene) 
			{
				//std::copy(std::begin(other.entitiesList), std::end(other.entitiesList), std::back_inserter(entitiesList));
				entitiesList = _scene.entitiesList;
			};*/
		
			~Scene();

			Scene& operator= (const Scene& _scene) = delete;
			Scene& operator= (const Scene&& _scene) = delete;

			void Start() override
			{
				for (auto entity : Scene::Instance()->m_entitiesList) {
					entity->Start();
				}
			}

			void Update() override
			{
				for (auto entity : Scene::Instance()->m_entitiesList) {
					entity->Update();
				}
			}

			void OnGUI() override
			{
				for (auto entity : Scene::Instance()->m_entitiesList) {
					entity->OnGUI();
				}
			}

			void OnRender() override
			{
				for (auto entity : Scene::Instance()->m_entitiesList) {
					entity->OnRender();
				}
			}

			void Add(Entity* _entity)
			{
				Scene::Instance()->m_entitiesList.push_back(_entity);
			}

			static Scene* Instance()
			{
				if (Scene::m_instance == nullptr)
				{
					Scene::m_instance = new Scene();
				}
				return m_instance;
			}

			static Camera* GetMainCamera()
			{
				return Scene::Instance()->m_mainCamera;
			}

			virtual void InitSceneSettings();
			
			// static void ProcessInput(GLFWwindow* w) {} ;

		private:
			std::vector<Entity*> m_entitiesList;
			static Scene* m_instance; // singleton instance
			Camera* m_mainCamera;
	};
}
