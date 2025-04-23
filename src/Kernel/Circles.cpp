#include "Kernel/Circles.hpp"
#include "Kernel/Constants.hpp"
#include "Kernel/Exceptions.hpp"

namespace Isaac
{

  Circle::Circle(const Vector2f& position_, const float& mass_, const float& radius_) : Shape(position_, mass_, ShapeTypes2D::Circle)
  {
    if (radius_ < LENGTH_PRECISION) throw Isaac::NegativeLengthException("Circle radius must be positive");
    radius = radius_;
  }

  Circle::Circle(const Circle&& circle_) noexcept : Circle(circle_.getPositionVector(), circle_.getMass(), circle_.getRadius()) {}

  float Circle::getRadius() const noexcept {return radius;}

}; // namespace Isaac