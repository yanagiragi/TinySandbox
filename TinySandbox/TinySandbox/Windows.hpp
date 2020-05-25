#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <functional>

namespace TinySandbox {

    
    class Windows 
    {
        public:
        
        virtual bool ShouldClose() = 0;
        virtual void MainLoop() = 0;
    };

    class GLFW_Windows : Windows 
    {
        public:

        GLFW_Windows(int width, int height, const char* title, ::GLFWmonitor *monitor, ::GLFWwindow *share);
        
        bool ShouldClose() ;

        void MainLoop() ;

        void SetInputCallback(std::function<void(GLFWwindow*)> _inputCallback) ;

        void SetRenderCallback(std::function<void(void)> _renderCallback) ;

        // helper function for now
        GLFWwindow* instance();

        ~GLFW_Windows()
        {
            glfwTerminate();
        }

        const char *name = "GLFW";

        private:

        GLFWwindow *m_glfwInstance;

        std::function<void(GLFWwindow*)> inputCallback;
        std::function<void(void)> renderCallback;
    };
}

