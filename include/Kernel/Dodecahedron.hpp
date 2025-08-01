#ifndef ISAAC_DODECAHEDRON_HPP
#define ISAAC_DODECAHEDRON_HPP

#include <Kernel/Body.hpp>

namespace Isaac {
  class Dodecahedron final : public Body {
  public:
    Dodecahedron() noexcept;

    Dodecahedron(const double &mass_, const double &radius_, const Vector3d &position_, const Vector3d &velocity_,
                 const Vector4d &color_) noexcept;

    Dodecahedron(const Dodecahedron &other) noexcept;

  private:
    static std::vector<Vector3d> constructDodecahedronVertices(const double &radius_) noexcept;
  };
} // namespace Isaac

#endif // ISAAC_DODECAHEDRON_HPP
