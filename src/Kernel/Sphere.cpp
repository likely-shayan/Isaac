#include "Kernel/Sphere.hpp"

namespace Isaac::Kernel {
Sphere::Sphere() noexcept = default;

Sphere::Sphere(const double &radius_,
               const Vector3d &position_,
               const Vector3d &velocity_,
               const Vector3d &acceleration_) noexcept
    : Curve3D(SphereType, position_, velocity_, acceleration_) {
  radius = radius_;
}

Sphere::Sphere(const Sphere &sphere_) noexcept
    : Sphere(sphere_.radius,
             sphere_.getPosition(),
             sphere_.getVelocity(),
             sphere_.getAcceleration()) {}

double Sphere::getRadius() const noexcept { return radius; }
} // namespace Isaac::Kernel
