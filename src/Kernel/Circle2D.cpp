#include "Kernel/Circle2D.hpp"

namespace Isaac::Kernel {

  Circle2D::Circle2D(const double& radius_, const Vector2d& position_, const Vector2d& velocity_, const Vector2d& acceleration_) noexcept 
  : Curve2D(CurveTypes2D::Circle, position_, velocity_, acceleration_) {
    radius = radius_;
  }

  Circle2D::Circle2D(const Circle2D& circle_) noexcept 
  : Circle2D(circle_.radius, circle_.getPosition(), circle_.getVelocity(), circle_.getAcceleration()) {}

  double Circle2D::getRadius() noexcept {return radius;}

} // namespace Isaac::Kernel