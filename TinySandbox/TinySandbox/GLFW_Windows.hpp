#pragma once

#include "Windows.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

namespace TinySandbox {

	class GLFW_Windows : public Windows
	{
		public:

			GLFW_Windows(int width, int height, const char* title, ::GLFWmonitor *monitor, ::GLFWwindow *share);
			~GLFW_Windows();

			bool ShouldClose();
			
			void Loop();

			void SetInputCallback(std::function<void(GLFWwindow*)> _inputCallback);

			void SetRenderCallback(std::function<void(void)> _renderCallback);

			GLFWwindow* instance(); // helper function for now
			
			const char *name = "GLFW";

		private:
			GLFWwindow *m_glfwInstance;

			std::function<void(GLFWwindow*)> inputCallback;
			std::function<void(void)> renderCallback;
	};
}

#pragma once
