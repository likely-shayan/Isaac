#include <Kernel/Octahedron.hpp>

namespace Isaac {
  Octahedron::Octahedron() noexcept = default;

  Octahedron::Octahedron(const double &mass_, const double &radius_, const Vector3d &position_,
                         const Vector3d &velocity_, const Vector4d &color_) noexcept : Body(
    mass_, constructOctahedronVertices(radius_), position_, velocity_, color_) {
  }

  Octahedron::Octahedron(const Octahedron &other) noexcept = default;

  std::vector<Vector3d> Octahedron::constructOctahedronVertices(const double &radius_) noexcept {
    Vector3d v0(0, radius_, 0);
    Vector3d v1(0, -radius_, 0);
    Vector3d v2(radius_, 0, 0);
    Vector3d v3(-radius_, 0, 0);
    Vector3d v4(0, 0, radius_);
    Vector3d v5(0, 0, -radius_);

    std::vector<Vector3d> vertices = {
      v0, v4, v2,
      v0, v2, v5,
      v0, v5, v3,
      v0, v3, v4,

      v1, v2, v4,
      v1, v5, v2,
      v1, v3, v5,
      v1, v4, v3
    };

    return vertices;
  }
} // namespace Isaac
