#include "Kernel/Curves2D.hpp"

namespace Isaac::Kernel {

  Curve2D::Curve2D(const CurveTypes2D& curveType_, const Vector2d& position_, const Vector2d& velocity_, const Vector2d& acceleration_) noexcept
  : curveType(curveType_), position(position_), velocity(velocity_), acceleration(acceleration_) {}

  Curve2D::Curve2D(const Curve2D& curve) noexcept : Curve2D(curve.getCurveType(), curve.getPosition(), curve.getVelocity(), curve.getAcceleration()) {}

  CurveTypes2D Curve2D::getCurveType() const noexcept {return curveType;}

  Vector2d Curve2D::getPosition() const noexcept {return position;}

  void Curve2D::setPosition(const Vector2d& newPosition) noexcept {position = newPosition;}

  Vector2d Curve2D::getVelocity() const noexcept {return velocity;}

  void Curve2D::setVelocity(const Vector2d& newVelocity) noexcept {velocity = newVelocity;}

  Vector2d Curve2D::getAcceleration() const noexcept {return acceleration;}

  void Curve2D::setAcceleration(const Vector2d& newAcceleration) noexcept {acceleration = newAcceleration;}

} // namespace Isaac::Kernel