#include "Scene.hpp"

#include "TestComponent.hpp"

#include "GLFW_Windows.hpp"

// initialize static member
TinySandbox::Scene* TinySandbox::Scene::m_instance = nullptr;

namespace TinySandbox
{
	// ctor, Setup Scene
	Scene::Scene()
	{

	}

	void Scene::InitSceneSettings()
	{
		TinySandbox::Component* testComponent = new TinySandbox::TestComponent();

		TinySandbox::Entity* testEntity = new TinySandbox::Entity();
		testEntity->Add(testComponent);

		Scene::Instance()->Add(testEntity);
	}

	void Scene::Draw()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		std::cout << Scene::Instance() << std::endl;

		Scene::Instance()->Start();
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
