#include "Kernel/Curve3D.hpp"

namespace Isaac::Kernel {
  
  Curve3D::Curve3D() noexcept = default;

  Curve3D::Curve3D(const CurveType3D& curveType_, const Vector3d& position_, const Vector3d& velocity_, const Vector3d& acceleration_) noexcept
  : curveType(curveType_), position(position_), velocity(velocity_), acceleration(acceleration_) {}

  Curve3D::Curve3D(const Curve3D& curve) noexcept : Curve3D(curve.getCurveType(), curve.getPosition(), curve.getVelocity(), curve.getAcceleration()) {}

  CurveType3D Curve3D::getCurveType() const noexcept {return curveType;}

  Vector3d Curve3D::getPosition() const noexcept {return position;}

  void Curve3D::setPosition(const Vector3d& newPosition) noexcept {position = newPosition;}

  Vector3d Curve3D::getVelocity() const noexcept {return velocity;}

  void Curve3D::setVelocity(const Vector3d& newVelocity) noexcept {velocity = newVelocity;}

  Vector3d Curve3D::getAcceleration() const noexcept {return acceleration;}

  void Curve3D::setAcceleration(const Vector3d& newAcceleration) noexcept {acceleration = newAcceleration;}

} // namespace Isaac::Kernel