#include <iostream>

#include <Eigen/Dense>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <Kernel/Constants.hpp>
#include <Rendering/Shader.hpp>
#include <Rendering/Window.hpp>
#include <Rendering/Camera.hpp>

using Eigen::Vector4d;
using Eigen::Matrix4d;
using Eigen::Affine3d;
using Eigen::Translation3d;

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

    glEnable(GL_DEPTH_TEST);
    camera = Camera({0, 0, 3});
    shader = Shader("src/Rendering/VertexShader.vert", "src/Rendering/FragmentShader.frag");
  }

  void Window::Run() noexcept {
    const std::size_t n = mesh->getSize();

    unsigned int VBOs[n], VAOs[n];
    glGenVertexArrays(n, VAOs);
    glGenBuffers(n, VBOs);

    for (std::size_t i = 0; i < n; ++i) {
      std::vector<float> vertices = mesh->getVertices(i);

      glBindVertexArray(VAOs[i]);
      glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
      glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
    }

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE) {
        std::exit(EXIT_SUCCESS);
      }

      glClearColor(BACKGROUND_COLOUR);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      shader.Use();

      mesh->updateBodies();

      Matrix4d projection;
      double fov_rad = 45.0 * M_PI / 180.0;
      double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
      double near_plane = 0.1;
      double far_plane = 100.0;
      double t = tan(fov_rad / 2.0) * near_plane;
      double r = t * aspect;
      projection << near_plane/r, 0, 0, 0,
                    0, near_plane/t, 0, 0,
                    0, 0, -(far_plane + near_plane)/(far_plane - near_plane), -2*far_plane*near_plane/(far_plane-near_plane),
                    0, 0, -1, 0;

      Matrix4d view = camera.getViewMatrix();
      shader.setMatrix4("projection", projection);
      shader.setMatrix4("view", view);

      for (std::size_t i = 0; i < n; ++i) {
        Vector3d position = mesh->getBody(i)->getPosition();

        Affine3d model_transform{Translation3d(position)};

        Matrix4d model = model_transform.matrix();

        shader.setMatrix4("model", model);
        shader.setVector4("Color", mesh->getBody(i)->getColor());

        glBindVertexArray(VAOs[i]);
        glDrawArrays(GL_TRIANGLES, 0, mesh->getBody(i)->getVertexCount());
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
