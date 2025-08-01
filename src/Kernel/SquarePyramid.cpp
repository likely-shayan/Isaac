#include <Kernel/SquarePyramid.hpp>

namespace Isaac {
  SquarePyramid::SquarePyramid() noexcept {
  }

  SquarePyramid::SquarePyramid(const double &mass_, const double &sideLength_, const double &height_,
                               const Vector3d &position_, const Vector3d &velocity_,
                               const Vector4d &color_) noexcept : Body(
    mass_, constructSquarePyramidVertices(sideLength_, height_), position_, velocity_, color_) {
  }

  SquarePyramid::SquarePyramid(const SquarePyramid &other) noexcept : Body(other) {
  }

  std::vector<Vector3d> SquarePyramid::constructSquarePyramidVertices(const double &sideLength_,
                                                                      const double &height_) noexcept {
    const double halfSide = sideLength_ / 2.0;
    const double halfHeight = height_ / 2.0;

    Vector3d v0(-halfSide, -halfHeight, -halfSide);
    Vector3d v1(halfSide, -halfHeight, -halfSide);
    Vector3d v2(halfSide, -halfHeight, halfSide);
    Vector3d v3(-halfSide, -halfHeight, halfSide);
    Vector3d v4(0, halfHeight, 0);

    std::vector vertices = {
      v0, v1, v2,
      v0, v2, v3,

      v0, v1, v4,
      v1, v2, v4,
      v2, v3, v4,
      v3, v0, v4
    };

    return vertices;
  }
} // namespace Isaac
