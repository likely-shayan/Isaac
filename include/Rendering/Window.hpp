#ifndef ISAAC_WINDOW_HPP_
#define ISAAC_WINDOW_HPP_

#include <Kernel/Mesh.hpp>
#include <Rendering/Shader.hpp>
#include <Rendering/Camera.hpp>

#include <GLFW/glfw3.h>

namespace Isaac {
  class Window {
  public:
    Window() noexcept;

    explicit Window(const std::shared_ptr<Mesh> &mesh_) noexcept;

    void Run() noexcept;

    ~Window() noexcept;

  private:
    void processInput(GLFWwindow *window) noexcept;

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) noexcept;

    static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) noexcept;

    GLFWwindow *window;
    std::shared_ptr<Mesh> mesh;
    Shader shader;
    Camera camera;
    double deltaTime = 0, lastFrame = 0, lastX, lastY;
    bool firstMouse = true;
  };
} // namespace Isaac

#endif // ISAAC_WINDOW_HPP_
