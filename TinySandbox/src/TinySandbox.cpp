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

	TinySandbox::GLFW_Windows* window = new TinySandbox::GLFW_Windows(SCR_WIDTH, SCR_HEIGHT, "NSD!", NULL, NULL);
	TinySandbox::Scene* mainScene = TinySandbox::Scene::Instance();

	TinySandbox::GLFW_Windows::SetInstance(window);

	// for reshape callback, the last parameter is a function point
	// there is no way to cast it from a lambda or std::function
	// and it has to be static function
	glfwSetFramebufferSizeCallback(window->GetGLFWInstance(), framebuffer_size_callback);

	// Mouse Callback
	// glfwSetCursorPosCallback(window->instance(), mouse_callback);	

	window->SetInputCallback(ProcessInput);

	window->SetScene(mainScene);
	
	// init scene after mainScene is attached to Windows
	// The reason is scene need windows_instance to hold viewport settings"
	mainScene->InitSceneSettings();

	TinySandbox::GLFW_Windows::GetInstance()->Loop();

	// cleanup resources
	delete apiInstance;

	return 0;
}

