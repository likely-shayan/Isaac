#ifndef ISAAC_SPHERE_HPP
#define ISAAC_SPHERE_HPP

#include <Kernel/Body.hpp>

namespace Isaac {
  class Sphere final : public Body {
  public:
    Sphere() noexcept;

    Sphere(const double &mass_, const double &radius_, const Vector3d &position_, const Vector3d &velocity_,
           const Vector4d &color_) noexcept;

    Sphere(const Sphere &other) noexcept;

  private:
    static std::vector<Vector3d> constructSphereVertices(const double &radius_) noexcept;
  };
} // namespace Isaac

#endif // ISAAC_SPHERE_HPP
