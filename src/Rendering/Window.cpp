#include "Rendering/Window.hpp"

namespace Isaac::Rendering
{
    Window::Window() = default;

    Window::Window(const int& width,
                   const int& height,
                   const std::string& windowTitle,
                   const std::array<float, 4>& color)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);

        if (window == NULL) { glfwTerminate(); }
        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, this->framebuffer_size_callback);

        gladLoadGL(glfwGetProcAddress);

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(color[0], color[1], color[2], color[3]);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
} // namespace Isaac::Rendering
