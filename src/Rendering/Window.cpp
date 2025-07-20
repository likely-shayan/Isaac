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
    lastX = SCREEN_WIDTH / 2.0;
    lastY = SCREEN_HEIGHT / 2.0;
  }

  Window::Window(const std::shared_ptr<Mesh> &mesh_) noexcept {
    mesh = mesh_;

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
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGL(glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD" << std::endl;
      glfwTerminate();
      std::exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
    camera = Camera({CAMERA_INITIAL_POSITION}, {0, 1, 0}, -90.0, 0.0);
    shader = Shader("src/Rendering/VertexShader.vert", "src/Rendering/FragmentShader.frag");

    lastX = SCREEN_WIDTH / 2.0;
    lastY = SCREEN_HEIGHT / 2.0;
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
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
      glEnableVertexAttribArray(0);
    }

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
      const double currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      processInput(window);

      glClearColor(BACKGROUND_COLOUR);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      shader.Use();

      mesh->updateBodies();

      constexpr double fov = CAMERA_FOV;
      constexpr double aspect = static_cast<double>(SCREEN_WIDTH) / static_cast<double>(SCREEN_HEIGHT);
      constexpr double near_plane = CAMERA_NEAR;
      constexpr double far_plane = CAMERA_FAR;

      Matrix4d projection = Matrix4d::Zero();
      const double f = 1.0 / tan((fov * M_PI / 180.0) / 2.0);
      projection(0, 0) = f / aspect;
      projection(1, 1) = f;
      projection(2, 2) = -(far_plane + near_plane) / (far_plane - near_plane);
      projection(2, 3) = -(2.0 * far_plane * near_plane) / (far_plane - near_plane);
      projection(3, 2) = -1.0;
      Matrix4d view = camera.getViewMatrix();

      shader.setMatrix4("projection", projection);
      shader.setMatrix4("view", view);

      for (std::size_t i = 0; i < n; ++i) {
        Vector3d position = mesh->getBody(i)->getPosition();
        Matrix4d model = Matrix4d::Identity();
        model(0, 3) = position.x();
        model(1, 3) = position.y();
        model(2, 3) = position.z();
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

  Window::~Window() noexcept {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void Window::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) noexcept {
    glViewport(0, 0, width, height);
  }

  void Window::processInput(GLFWwindow *window) noexcept {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      camera.processKeyboard(Camera::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      camera.processKeyboard(Camera::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      camera.processKeyboard(Camera::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      camera.processKeyboard(Camera::RIGHT, deltaTime);
  }

  void Window::mouse_callback(GLFWwindow *window, double xposIn, double yposIn) noexcept {
    auto *instance = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (instance == nullptr) return;

    const double xpos = xposIn;
    const double ypos = yposIn;

    if (instance->firstMouse) {
      instance->lastX = xpos;
      instance->lastY = ypos;
      instance->firstMouse = false;
    }

    const double xoffset = xpos - instance->lastX;
    const double yoffset = instance->lastY - ypos;

    instance->lastX = xpos;
    instance->lastY = ypos;

    instance->camera.processMouseMovement(xoffset, yoffset);
  }
} // namespace Isaac
