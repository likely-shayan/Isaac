#ifndef ISAAC_OCTAHEDRON_HPP
#define ISAAC_OCTAHEDRON_HPP

#include <Kernel/Body.hpp>

namespace Isaac {
  class Octahedron final : public Body {
  public:
    Octahedron() noexcept;

    Octahedron(const double &mass_, const double &radius_, const Vector3d &position_, const Vector3d &velocity_,
               const Vector4d &color_) noexcept;

    Octahedron(const Octahedron &other) noexcept;

  private:
    static std::vector<Vector3d> constructOctahedronVertices(const double &radius_) noexcept;
  };
} // namespace Isaac

#endif // ISAAC_OCTAHEDRON_HPP
