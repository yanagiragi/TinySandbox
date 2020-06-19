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

			GLFW_Windows();
			GLFW_Windows(int width, int height, const char* title, ::GLFWmonitor *monitor, ::GLFWwindow *share);
			~GLFW_Windows();
			bool ShouldClose();			
			void Loop();
			void SetInputCallback(std::function<void(GLFWwindow*)> _inputCallback);			
			GLFWwindow* GetGLFWInstance();
			
		private:
			GLFWwindow *m_glfwInstance;			
			std::function<void(GLFWwindow*)> inputCallback;
	};
}
