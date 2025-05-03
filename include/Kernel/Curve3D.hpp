#ifndef CURVE_3D_HPP_
#define CURVE_3D_HPP_

#include <eigen3/Eigen/Dense>

using Eigen::Vector3d;

namespace Isaac::Kernel {
  
  enum CurveType3D {SphereType, };

  class Curve3D {
  public:

    Curve3D() noexcept;

    Curve3D(const CurveType3D& curveType_, const Vector3d& position_, const Vector3d& velocity_, const Vector3d& acceleration_) noexcept;

    Curve3D(const Curve3D& curve_) noexcept;

    CurveType3D getCurveType() const noexcept;

    Vector3d getPosition() const noexcept;

    void setPosition(const Vector3d& newPosition) noexcept;

    Vector3d getVelocity() const noexcept;

    void setVelocity(const Vector3d& newVelocity) noexcept;

    Vector3d getAcceleration() const noexcept;

    void setAcceleration(const Vector3d& newAcceleration) noexcept;

  private:

    CurveType3D curveType;
    Vector3d position, velocity, acceleration;
  };
  
} // namespace Isaac::Kernel

#endif // CURVE_3D_HPP_