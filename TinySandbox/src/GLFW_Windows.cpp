#include "GLFW_Windows.hpp"

#include "GraphicsAPI.hpp"

namespace TinySandbox
{
    GLFW_Windows::GLFW_Windows
	(int width, int height, const char* title, ::GLFWmonitor *monitor, ::GLFWwindow *share) 
	{
		glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		
        this->m_glfwInstance = glfwCreateWindow(width, height, title, monitor, share);

        if (this->m_glfwInstance == nullptr) {
            glfwTerminate();
            throw  "Failed to create GLFW window";
        }

        // TODO: below line should solve dependenccy with openGL
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
        #endif

        glfwMakeContextCurrent(this->m_glfwInstance);

        // glad: load all OpenGL function pointers
        // TODO: below line should solve dependenccy with openGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw "Failed to initialize GLAD";
        }
    }

	GLFW_Windows::~GLFW_Windows()
	{
		glfwTerminate();
	}

        
    bool GLFW_Windows::ShouldClose() {
        return glfwWindowShouldClose(this->m_glfwInstance);
    }

    void GLFW_Windows::Loop() {

		GraphicsAPI* API = GraphicsAPI::GetAPI();

		mainScene->Start();

        while (this->ShouldClose() == false)
        {
			// 0. Init Screen
			API->ClearScreenColor();
			API->ClearScreenDepth();
			API->ClearScreenStencil();

			// 1. Process Input
            this->inputCallback(this->m_glfwInstance);

			// 2. Update Game Logics
			mainScene->Update();

			// 3. Render the scene without UI
			mainScene->OnRender();

			// 4. Render UI after the scene
			mainScene->OnGUI();

			// 5. Flush FrameBuffer
            glfwSwapBuffers(this->m_glfwInstance);
            glfwPollEvents();
        }
    }

	/*void GLFW_Windows::SetInputCallback(void (_inputCallback)(GLFWwindow*)) {
		//this->inputCallback = _inputCallback;
	}*/

    void GLFW_Windows::SetInputCallback(std::function<void(GLFWwindow*)> _inputCallback) {
		this->inputCallback = _inputCallback;
    }

    // helper function for now
    GLFWwindow* GLFW_Windows::instance() {
        return this->m_glfwInstance;
    }
}
