#ifndef CURVE_2D_HPP_
#define CURVE_2D_HPP_

#include <eigen3/Eigen/Dense>

using Eigen::Vector2d;

namespace Isaac::Kernel {

  enum CurveType2D {CircleType, };

  class Curve2D {
  public:

    Curve2D() noexcept;

    Curve2D(const CurveType2D& curveType_, const Vector2d& position_, const Vector2d& velocity_, const Vector2d& acceleration_) noexcept;

    Curve2D(const Curve2D& curve_) noexcept;

    CurveType2D getCurveType() const noexcept;

    Vector2d getPosition() const noexcept;

    void setPosition(const Vector2d& newPosition) noexcept;

    Vector2d getVelocity() const noexcept;

    void setVelocity(const Vector2d& newVelocity) noexcept;

    Vector2d getAcceleration() const noexcept;

    void setAcceleration(const Vector2d& newAcceleration) noexcept;

  private:
  
    CurveType2D curveType;
    Vector2d position, velocity, acceleration;
  };
  
} // namespace Isaac::Kernel

#endif // CURVE_2D_HPP_