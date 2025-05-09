#ifndef RENDERABLE_OBJECT_2D_HPP_
#define RENDERABLE_OBJECT_2D_HPP_

#include "../Kernel/RigidBody2D.hpp"
#include <vector>

using Isaac::Kernel::RigidBody2D;

namespace Isaac::Rendering {

    class Renderable_Object_2D {
    public:

      Renderable_Object_2D() noexcept;

      Renderable_Object_2D(const RigidBody2D& body_, const std::vector<float>& color_, const int& screen_Width_, const int& screen_Height_) noexcept;

      Renderable_Object_2D(const Renderable_Object_2D& renderable_Object_2D_) noexcept;

      std::vector<float> getCoordinates() const noexcept;

      std::vector<int> getIndices() const noexcept;

      std::vector<float> getColor() const noexcept;

    private:
      int screen_Width, screen_Height;
      RigidBody2D body;
      std::vector<float> color;
      std::vector<float> Coordinates;
      std::vector<int> indices;

      static std::vector<float> decompose_2D_Coordinates(const int& screenWidth_, const int& screenHeight_, const Vector2f& vector_) noexcept;
    };

} // namespace Isaac::Rendering

#endif // RENDERABLE_OBJECT_2D_HPP_
