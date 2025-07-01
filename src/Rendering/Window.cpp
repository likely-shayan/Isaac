#include <iostream>
#include <chrono>
#include <thread>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <Kernel/Constants.hpp>
#include <Rendering/Window.hpp>

namespace Isaac {
  Window::Window() noexcept {
    window = nullptr;
    mesh = nullptr;
  }

  Window::Window(Mesh *mesh_) noexcept {
    mesh = mesh_;

    const std::size_t n = mesh->getSize();

    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "\n"
        "uniform vec3 deltaPos;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos + deltaPos, 1.0);\n"
        "}\0";

    auto getFragmentShaderSource = [this](const std::size_t &i) -> std::string {
      const std::vector<float> &color = mesh->getBody(i)->getColor();
      std::string FragColor;
      for (const float &val: color) {
        FragColor += std::to_string(val);
        FragColor += &val == &color.back() ? "f" : "f, ";
      }
      const std::string fragmentShaderSource = "#version 330 core\n"
                                               "out vec4 FragColor;\n"
                                               "void main()\n"
                                               "{\n"
                                               "   FragColor = vec4(" + FragColor + ");\n"
                                               "}\n";
      return fragmentShaderSource;
    };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
    if (window == nullptr) {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGL(glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD" << std::endl;
      glfwTerminate();
      std::exit(EXIT_FAILURE);
    }

    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const std::vector<unsigned int> fragmentShader(n, glCreateShader(GL_FRAGMENT_SHADER));
    shaderPrograms.resize(n);
    for (unsigned int &shader: shaderPrograms) { shader = glCreateProgram(); }

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    for (std::size_t i = 0; i < n; ++i) {
      const std::string fragmentShaderSourceStr = getFragmentShaderSource(i);
      const char *fragmentShaderSource = fragmentShaderSourceStr.c_str();
      glShaderSource(fragmentShader[i], 1, &fragmentShaderSource, nullptr);
      glCompileShader(fragmentShader[i]);
      glAttachShader(shaderPrograms[i], vertexShader);
      glAttachShader(shaderPrograms[i], fragmentShader[i]);
      glLinkProgram(shaderPrograms[i]);
    }
  }

  void Window::Run() const noexcept {
    const std::chrono::duration<double, std::milli> oneSecond(1.0 / TIME_STEP);
    const std::size_t n = mesh->getSize();

    unsigned int VBOs[n], VAOs[n];
    glGenVertexArrays(n, VAOs);
    glGenBuffers(n, VBOs);

    for (std::size_t i = 0; i < n; ++i) {
      glBindVertexArray(VAOs[i]);
      glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
      glEnableVertexAttribArray(0);
    }

    while (!glfwWindowShouldClose(window)) {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE) {
        std::exit(EXIT_SUCCESS);
      }

      auto start = std::chrono::steady_clock::now();

      for (int j = 0; j < static_cast<int>(1.0 / TIME_STEP); ++j) {
        glClearColor(BACKGROUND_COLOUR);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh->updateBodies();

        for (std::size_t i = 0; i < n; ++i) {
          std::vector<float> polygonVertices = adjustedVertices(mesh->getVertices(i));

          glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
          glBufferData(GL_ARRAY_BUFFER, sizeof(float) * polygonVertices.size(), polygonVertices.data(),
                       GL_DYNAMIC_DRAW);

          const unsigned int vertexCount = mesh->getBody(i)->getVertexCount();

          glUseProgram(shaderPrograms[i]);
          glBindVertexArray(VAOs[i]);

          glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
      }

      auto end = std::chrono::steady_clock::now();
      if (std::chrono::duration<double, std::milli> elapsed = end - start; elapsed < oneSecond) {
        std::this_thread::sleep_for(oneSecond - elapsed);
      }
    }
    glDeleteVertexArrays(n, VAOs);
    glDeleteBuffers(n, VBOs);
    for (const unsigned int &shader: shaderPrograms) {
      glDeleteProgram(shader);
    }
  }

  std::vector<float> Window::adjustedVertices(const std::vector<double> &vertices) noexcept {
    const std::size_t n = vertices.size();
    std::vector<float> adjustedVertices(n);

    for (std::size_t i = 0; i < n; i += 3) {
      adjustedVertices[i] = vertices[i] / WORLD_WIDTH;
      adjustedVertices[i + 1] = vertices[i + 1] / WORLD_HEIGHT;
      adjustedVertices[i + 2] = vertices[i + 2] / WORLD_DEPTH;
    }

    return adjustedVertices;
  }

  Window::~Window() noexcept {
    glfwTerminate();
  }

  void Window::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) noexcept {
    glViewport(0, 0, width, height);
  }
} // namespace Isaac
