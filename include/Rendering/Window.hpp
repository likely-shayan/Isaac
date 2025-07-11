#ifndef ISAAC_WINDOW_HPP_
#define ISAAC_WINDOW_HPP_

#include <GLFW/glfw3.h>
#include <Kernel/Mesh.hpp>

namespace Isaac {
  class Window {
  public:
    Window() noexcept;

    explicit Window(std::unique_ptr<Mesh> mesh_) noexcept;

    void Run() const noexcept;

    static std::vector<float> adjustedVertices(const std::vector<double> &vertices) noexcept;

    ~Window() noexcept;

  private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) noexcept;

    GLFWwindow *window;
    std::unique_ptr<Mesh> mesh;
    std::vector<unsigned int> shaderPrograms;
  };
} // namespace Isaac

#endif // ISAAC_WINDOW_HPP_
