#ifndef ISAAC_ICOSAHEDRON_HPP
#define ISAAC_ICOSAHEDRON_HPP

#include <Kernel/Body.hpp>

namespace Isaac {
  class Icosahedron final : public Body {
  public:
    Icosahedron() noexcept;

    Icosahedron(const double &mass_, const double &radius_, const Vector3d &position_, const Vector3d &velocity_,
                const Vector4d &color_) noexcept;

    Icosahedron(const Icosahedron &other) noexcept;

  private:
    static std::vector<Vector3d> constructIcosahedronVertices(const double &radius_) noexcept;
  };
} // namespace Isaac

#endif // ISAAC_ICOSAHEDRON_HPP
