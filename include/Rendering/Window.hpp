#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <array>
#include <string>
#include <vector>

#include "Renderable_Object_2D.hpp"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

namespace Isaac::Rendering
{

  class Window {
  public:

    Window();

    Window(const int& width, const int& height, const std::string& windowTitle, const std::array<float, 4>& color, const std::vector<Renderable_Object_2D>& renderable_Objects);

  private:

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    GLFWwindow* window = nullptr;
  };
  
} // namespace Isaac::Rendering

#endif // WINDOW_HPP_