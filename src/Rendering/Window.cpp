#include <iostream>

#include <Eigen/Dense>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <Kernel/Constants.hpp>
#include <Rendering/Shader.hpp>
#include <Rendering/Window.hpp>

using Eigen::Vector4d;

namespace Isaac {
  Window::Window() noexcept {
    window = nullptr;
    mesh = nullptr;
  }

  Window::Window(std::unique_ptr<Mesh> mesh_) noexcept {
    mesh = std::move(mesh_);

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

    shader = Shader("src/Rendering/VertexShader.vert", "src/Rendering/FragmentShader.frag");
  }

  void Window::Run() const noexcept {
    const std::size_t n = mesh->getSize();

    unsigned int VBOs[n], VAOs[n];
    glGenVertexArrays(n, VAOs);
    glGenBuffers(n, VBOs);

    for (std::size_t i = 0; i < n; ++i) {
      glBindVertexArray(VAOs[i]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->getBody(i)->getVertexCount(),
                   adjustedVertices(mesh->getVertices(i)).data(),GL_DYNAMIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
      glEnableVertexAttribArray(0);
      glBindVertexArray(VAOs[i]);
    }

    while (!glfwWindowShouldClose(window)) {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE) {
        std::exit(EXIT_SUCCESS);
      }

      glClearColor(BACKGROUND_COLOUR);
      glClear(GL_COLOR_BUFFER_BIT);

      shader.Use();

      mesh->updateBodies();

      for (std::size_t i = 0; i < n; ++i) {
        std::vector<float> polygonVertices = adjustedVertices(mesh->getVertices(i));

        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * polygonVertices.size(), polygonVertices.data(),
                     GL_DYNAMIC_DRAW);

        const unsigned int vertexCount = mesh->getBody(i)->getVertexCount();

        glBindVertexArray(VAOs[i]);

        shader.setVector4("Color", mesh->getBody(i)->getColor());
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
    glDeleteVertexArrays(n, VAOs);
    glDeleteBuffers(n, VBOs);
  }

  std::vector<float> Window::adjustedVertices(const std::vector<float> &vertices) noexcept {
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
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void Window::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) noexcept {
    glViewport(0, 0, width, height);
  }
} // namespace Isaac
