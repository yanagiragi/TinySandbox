// always include GraphicsAPI first, since it may contains header need to include first
#include "GraphicsAPI_OpenGL.hpp"

#include "GLFW_Windows.hpp"

#include "Scene.hpp"

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// declare as a global variable for reshape 
TinySandbox::GLFW_Windows* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void Draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);	
}

void ProcessInput(GLFWwindow *window)
{
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, true);

	TinySandbox::Camera* mainCamera = TinySandbox::Scene::GetMainCamera();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mainCamera->Phi(mainCamera->Phi() + 1);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mainCamera->Phi(mainCamera->Phi() - 1);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mainCamera->Theta(mainCamera->Theta() + 1);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mainCamera->Theta(mainCamera->Theta() - 1);
	}

	/*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{	
		glm::vec3 position = mainCamera->Position();

		mainCamera->Position(position + glm::vec3(0, 0, 1));
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		TinySandbox::Camera* mainCamera = TinySandbox::Scene::GetMainCamera();

		glm::vec3 position = mainCamera->Position();

		mainCamera->Position(position + glm::vec3(0, 0, -1));
	}*/

		
}

void framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	std::cout << window->name << std::endl;
}

int main()
{
	// Note: the constructor binds GrpahicsAPI::m_api to the instance
	// The reason is there should only be one api in entire engine
	// However we provide SetAPI() if multiple api instance exists
	const TinySandbox::GraphicsAPI_OpenGL* apiInstance = new TinySandbox::GraphicsAPI_OpenGL();

	window = new TinySandbox::GLFW_Windows(SCR_WIDTH, SCR_HEIGHT, "NSD!", NULL, NULL);

	TinySandbox::Scene* mainScene = TinySandbox::Scene::Instance();

	// for reshape callback, the last parameter is a function point
	// there is no way to cast it from a lambda or std::function
	// and it has to be static function
	glfwSetFramebufferSizeCallback(window->instance(), framebuffer_size_callback);

	window->SetInputCallback(ProcessInput);
	window->SetRenderCallback(TinySandbox::Scene::Draw);
	TinySandbox::Scene::Instance()->InitSceneSettings();
	window->SetScene(mainScene);

	window->Loop();

	// cleanup resources
	delete window;
	delete apiInstance;

	return 0;
}

