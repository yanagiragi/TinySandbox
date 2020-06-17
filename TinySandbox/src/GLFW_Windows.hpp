#pragma once

#include "Windows.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow *window);

namespace TinySandbox {

	class GLFW_Windows : public Windows
	{
		public:

			GLFW_Windows(int width, int height, const char* title, ::GLFWmonitor *monitor, ::GLFWwindow *share);
			~GLFW_Windows();

			bool ShouldClose();
			
			void Loop();

			void SetInputCallback(std::function<void(GLFWwindow*)> _inputCallback);
			// void SetInputCallback(void(*_inputCallback)(GLFWwindow*));
			//void SetInputCallback(void (TinySandbox::Scene::*ProcessInput)(GLFWwindow*));

			GLFWwindow* instance(); // helper function for now			
			const char *name = "GLFW";

		private:
			
			GLFWwindow *m_glfwInstance;
			
			std::function<void(GLFWwindow*)> inputCallback;
			// void(*inputCallback)(GLFWwindow*);
			
			std::function<void(void)> renderCallback;
	};
}
