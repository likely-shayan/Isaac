#include "Circles.hpp"
#include "Constants.hpp"
#include "Exceptions.hpp"

namespace Isaac
{

  Circle::Circle(const Vector2f& position_, const Vector2f& direction_, const float& mass_, const float& radius_) : Shape(position_, direction_, mass_, ShapeTypes2D::Circle)
  {
    if (radius_ < LENGTH_PRECISION) throw Isaac::NegativeLengthException("Circle radius must be positive");
    radius = radius_;
  }

  Circle::Circle(const Circle&& circle_) noexcept : Circle(circle_.getPositionVector(), circle_.getDirectionVector(), circle_.getMass(), circle_.getRadius()) {}

  float Circle::getRadius() const noexcept {return radius;}

}; // namespace Isaac