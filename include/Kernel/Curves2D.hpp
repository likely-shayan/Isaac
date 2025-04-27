#ifndef CURVES_2D_HPP_
#define CURVES_2D_HPP_

#include <eigen3/Eigen/Dense>

using Eigen::Vector2d;

namespace Isaac::Kernel {

  enum CurveTypes2D {Circle, };

  class Curve2D {
  public:

    Curve2D() noexcept = default;

    Curve2D(const CurveTypes2D& curveType_, const Vector2d& position_, const Vector2d& velocity_, const Vector2d& acceleration_) noexcept;

    Curve2D(const Curve2D& curve_) noexcept;

    CurveTypes2D getCurveType() const noexcept;

    Vector2d getPosition() const noexcept;

    void setPosition(const Vector2d& newPosition) noexcept;

    Vector2d getVelocity() const noexcept;

    void setVelocity(const Vector2d& newVelocity) noexcept;

    Vector2d getAcceleration() const noexcept;

    void setAcceleration(const Vector2d& newAcceleration) noexcept;

  private:
  
    CurveTypes2D curveType;
    Vector2d position, velocity, acceleration;
  };
  
} // namespace Isaac::Kernel

#endif // CURVES_2D_HPP_