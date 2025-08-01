#include <Kernel/Cube.hpp>

namespace Isaac {
  Cube::Cube() noexcept = default;

  Cube::Cube(const double &mass_, const double &length_, const Vector3d &position_, const Vector3d &velocity_,
             const Vector4d &color_) noexcept : Body(mass_, constructCubeVertices(length_), position_, velocity_,
                                                     color_) {
  }

  Cube::Cube(const Cube &other) noexcept = default;

  std::vector<Vector3d> Cube::constructCubeVertices(const double &length_) noexcept {
    const double halfSide = length_ / 2.0;

    const Vector3d v0(-halfSide, -halfSide, halfSide);
    const Vector3d v1(halfSide, -halfSide, halfSide);
    const Vector3d v2(halfSide, halfSide, halfSide);
    const Vector3d v3(-halfSide, halfSide, halfSide);
    const Vector3d v4(-halfSide, -halfSide, -halfSide);
    const Vector3d v5(halfSide, -halfSide, -halfSide);
    const Vector3d v6(halfSide, halfSide, -halfSide);
    const Vector3d v7(-halfSide, halfSide, -halfSide);

    std::vector vertices = {
      v0, v1, v2,
      v0, v2, v3,

      v4, v5, v6,
      v4, v6, v7,

      v4, v0, v3,
      v4, v3, v7,

      v1, v5, v6,
      v1, v6, v2,

      v3, v2, v6,
      v3, v6, v7,

      v4, v1, v0,
      v4, v5, v1
    };

    return vertices;
  }
} // namespace Isaac
