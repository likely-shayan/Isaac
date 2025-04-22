#ifndef CIRCLES_HPP_
#define CIRCLES_HPP_

#include "Shapes.hpp"

namespace Isaac
{

  class Circle : public Shape
  {
    float radius;
    public:
      Circle() noexcept = default;

      Circle(const Vector2f& position_, const Vector2f& direction_, const float& mass_, const float& radius_);

      Circle(const Circle&& circle_) noexcept;

      float getRadius() const noexcept;
  };

}; // namespace Isaac

#endif // CIRCLES_HPP_