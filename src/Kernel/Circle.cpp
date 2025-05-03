#include "Kernel/Circle.hpp"

namespace Isaac::Kernel {

  Circle::Circle() noexcept = default;

  Circle::Circle(const double& radius_, const Vector2d& position_, const Vector2d& velocity_, const Vector2d& acceleration_) noexcept 
  : Curve2D(CurveType2D::CircleType, position_, velocity_, acceleration_) {
    radius = radius_;
  }

  Circle::Circle(const Circle& circle_) noexcept 
  : Circle(circle_.radius, circle_.getPosition(), circle_.getVelocity(), circle_.getAcceleration()) {}

  double Circle::getRadius() noexcept {return radius;}

} // namespace Isaac::Kernel