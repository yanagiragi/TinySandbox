// always include GraphicsAPI first, since it may contains header need to include first
#include "GraphicsAPI_OpenGL.hpp"

#include "GLFW_Windows.hpp"
#include "Scene.hpp"

int main()
{
	// Note: the constructor binds GrpahicsAPI::m_api to the instance
	// The reason is there should only be one api in entire engine
	// However we provide SetAPI() if multiple api instance exists
	const TinySandbox::GraphicsAPI_OpenGL* apiInstance = new TinySandbox::GraphicsAPI_OpenGL();

	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	// declared in GLFW_Windows
	TinySandbox::GLFW_Windows* window = new TinySandbox::GLFW_Windows(SCR_WIDTH, SCR_HEIGHT, "NSD!", NULL, NULL);	

	// for reshape callback, the last parameter is a function point
	// there is no way to cast it from a lambda or std::function
	// and it has to be static function
	glfwSetFramebufferSizeCallback(window->instance(), framebuffer_size_callback);

	// Mouse Callback
	// glfwSetCursorPosCallback(window->instance(), mouse_callback);	

	window->SetInputCallback(ProcessInput);

	TinySandbox::Scene* mainScene = TinySandbox::Scene::Instance();
	mainScene->InitSceneSettings();
	
	window->SetScene(mainScene);
	window->Loop();

	// cleanup resources
	delete window;
	delete apiInstance;

	return 0;
}

