#include "Scene.hpp"

#include "GLFW_Windows.hpp"
#include "MeshRenderer.hpp"

#include "NormalDebugMaterial.hpp"

// initialize static member
TinySandbox::Scene* TinySandbox::Scene::m_instance = nullptr;

namespace TinySandbox
{
	// ctor, Setup Scene
	Scene::Scene()
	{
		m_mainCamera = new Camera();
	}

	Scene::~Scene()
	{
		delete m_mainCamera;
		if (Scene::Instance() != nullptr) {
			for (auto entity : Scene::Instance()->m_entitiesList)
			{
				delete entity;
			}
		}
	}

	void Scene::InitSceneSettings()
	{
		/***** Setup Graphics Setting *****/
		GraphicsAPI* API = GraphicsAPI::GetAPI();
		API->EnableDepthTest();
		
		/***** Setup Scene Entity & Setting *****/		
		TinySandbox::Entity* testEntity = new TinySandbox::Entity("Test");
		TinySandbox::MeshRenderer* meshRenderer = new TinySandbox::MeshRenderer();
		TinySandbox::Mesh mesh("../Resources/monkey.obj");
		Transform* testTransform = testEntity->GetTransform();

		testEntity->Add(meshRenderer); // implicitly cast to TinySandbox::Component
		meshRenderer->SetMesh(mesh);
		meshRenderer->SetMaterial(new NormalDebugMaterial(meshRenderer));
		testTransform->Rotation(glm::vec3(-90.0f, 0.0f, 90.0f));

		Scene::Instance()->Add(testEntity);
		
		// Main Camera Setting
		m_mainCamera->Aspect(1.33f);
		m_mainCamera->NearPlaneDistance(0.01f);
		m_mainCamera->FarPlaneDistance(100.0f);
		m_mainCamera->FieldOfView(45.0f);
		m_mainCamera->Position(glm::vec3(0, 0, 5));
		m_mainCamera->Phi(90.0f);
		m_mainCamera->Theta(0.0f);
	}

	/*void Scene::ProcessInput(GLFWwindow *window)
	{
		//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		//	glfwSetWindowShouldClose(window, true);
	}

	void Scene::framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);

		// std::cout << window->name << std::endl;
	}*/
}
