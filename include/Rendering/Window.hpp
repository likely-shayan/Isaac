#ifndef ISAAC_WINDOW_HPP_
#define ISAAC_WINDOW_HPP_

#include <Kernel/Mesh.hpp>
#include <Rendering/Shader.hpp>

#include <GLFW/glfw3.h>

namespace Isaac {
  class Window {
  public:
    Window() noexcept;

    explicit Window(std::unique_ptr<Mesh> mesh_) noexcept;

    void Run() const noexcept;

    static std::vector<float> adjustedVertices(const std::vector<float> &vertices) noexcept;

    ~Window() noexcept;

  private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) noexcept;

    GLFWwindow *window;
    std::unique_ptr<Mesh> mesh;
    Shader shader;
  };
} // namespace Isaac

#endif // ISAAC_WINDOW_HPP_
