#include "Rendering/Window.hpp"
#include <iostream>

namespace Isaac::Rendering
{
    Window::Window() = default;

    Window::Window(const int& width,
                   const int& height,
                   const std::string& windowTitle,
                   const std::array<float, 4>& color,
                   const std::vector<Renderable_Object_2D>& renderable_Objects
    )
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const int n = renderable_Objects.size();

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        std::vector<std::string> fragmentShaderSources(n);
        for (int i = 0; i < n; i++)
        {
            std::vector<float> C = renderable_Objects[i].getColor();
            fragmentShaderSources[i] = "#version 330 core\n"
                "out vec4 FragColor;\n"
                "void main()\n"
                "{\n"
                "   FragColor = vec4(" + std::to_string(C[0]) + "f, " + std::to_string(C[1]) + "f, " +
                std::to_string(C[2]) + "f, " + std::to_string(C[3]) + "f);\n"
                "}\n\0";
        }

        window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);

        if (window == NULL)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, this->framebuffer_size_callback);

        if (!gladLoadGL(glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return;
        }

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        std::vector<unsigned int> fragmentShaders(n);
        for (int i = 0; i < n; i++)
        {
            fragmentShaders[i] = glCreateShader(GL_FRAGMENT_SHADER);
            const char* constFragmentShaderSource = fragmentShaderSources[i].c_str();
            glShaderSource(fragmentShaders[i], 1, &constFragmentShaderSource, NULL);
            glCompileShader(fragmentShaders[i]);
        }

        std::vector<unsigned int> shaderPrograms(n);
        for (int i = 0; i < n; i++)
        {
            shaderPrograms[i] = glCreateProgram();
            glAttachShader(shaderPrograms[i], vertexShader);
            glAttachShader(shaderPrograms[i], fragmentShaders[i]);
            glLinkProgram(shaderPrograms[i]);
        }

        unsigned int VBOs[n], VAOs[n];
        glGenVertexArrays(n, VAOs);
        glGenBuffers(n, VBOs);

        std::vector<int> vertexCounts(n);

        for (int i = 0; i < n; i++)
        {
            const std::vector<float>& coordinates = renderable_Objects[i].getCoordinates();
            int totalFloats = coordinates.size();

            vertexCounts[i] = totalFloats / 3;

            glBindVertexArray(VAOs[i]);
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);

            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * totalFloats, coordinates.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(color[0], color[1], color[2], color[3]);
            glClear(GL_COLOR_BUFFER_BIT);

            for (int i = 0; i < n; i++)
            {
                glUseProgram(shaderPrograms[i]);

                glBindVertexArray(VAOs[i]);

                glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCounts[i]);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(n, VAOs);
        glDeleteBuffers(n, VBOs);
        for (int i = 0; i < n; i++)
        {
            glDeleteProgram(shaderPrograms[i]);
            glDeleteShader(fragmentShaders[i]);
        }
        glDeleteShader(vertexShader);

        glfwTerminate();
    }
} // namespace Isaac::Rendering
