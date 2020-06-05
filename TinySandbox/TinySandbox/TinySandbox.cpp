// always include GraphicsAPI first, since it may contains header need to include first
#include "GraphicsAPI.hpp"
#include "GLFW_Windows.hpp"

#include "Entity.hpp"

#include "TestComponent.hpp"

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// declare as a global variable for reshape 
TinySandbox::GLFW_Windows* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);	
}

void processInput(GLFWwindow *window)
{
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, true);
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
	// TODO: Should Create a Scene class, contains of Lists of Entity
	// replace mainLoopEntity to Scene

	TinySandbox::Entity mainLoopEntity;
	TinySandbox::Component* testComponent = new TinySandbox::TestComponent();

	// buggy when writing my own Add()
	mainLoopEntity.components.push_back(testComponent);
	//mainLoopComponent.Add(testComponent);

	window = new TinySandbox::GLFW_Windows(SCR_WIDTH, SCR_HEIGHT, "NSD!", NULL, NULL, mainLoopEntity);

	// for reshape callback, the last parameter is a function point
	// there is no way to cast it from a lambda or std::function
	// and it has to be static function
	glfwSetFramebufferSizeCallback(window->instance(), framebuffer_size_callback);

	window->SetInputCallback(processInput);
	window->SetRenderCallback(draw);

	std::cout << window->name << std::endl;

	window->MainLoop();

	// cleanup resources
	delete window;

	return 0;
}

