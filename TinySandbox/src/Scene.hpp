#pragma once

#include <glad/glad.h>

#include "Component.hpp"
#include "Entity.hpp"
#include "Camera.hpp"

#include <vector>

namespace TinySandbox
{
	class SkyboxRenderer;
}

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

			void Start() override;

			void Update() override;

			void OnGUI() override;

			void OnRender() override;

			void Add(Entity* _entity);

			static Scene* Instance();

			static Camera* GetMainCamera();

			virtual void InitSceneSettings();
			
			// static void ProcessInput(GLFWwindow* w) {} ;

		private:
			std::vector<Entity*> m_entitiesList;
			static Scene* m_instance; // singleton instance
			Camera* m_mainCamera;
			SkyboxRenderer* m_SkyboxRenderer;
	};
}
