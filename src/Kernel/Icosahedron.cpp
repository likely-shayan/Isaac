#include <Kernel/Icosahedron.hpp>

namespace Isaac {
  Icosahedron::Icosahedron() noexcept = default;

  Icosahedron::Icosahedron(const double &mass_, const double &radius_, const Vector3d &position_,
                           const Vector3d &velocity_, const Vector4d &color_) noexcept : Body(
    mass_, constructIcosahedronVertices(radius_), position_, velocity_, color_) {
  }

  Icosahedron::Icosahedron(const Icosahedron &other) noexcept = default;

  std::vector<Vector3d> Icosahedron::constructIcosahedronVertices(const double &radius_) noexcept {
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;

    std::array uniqueVertices = {
      Vector3d(-1, phi, 0), Vector3d(1, phi, 0), Vector3d(-1, -phi, 0), Vector3d(1, -phi, 0),
      Vector3d(0, -1, phi), Vector3d(0, 1, phi), Vector3d(0, -1, -phi), Vector3d(0, 1, -phi),
      Vector3d(phi, 0, -1), Vector3d(phi, 0, 1), Vector3d(-phi, 0, -1), Vector3d(-phi, 0, 1)
    };

    const double scale = radius_ / std::sqrt(1 + phi * phi);
    for (auto &v: uniqueVertices) {
      v *= scale;
    }

    std::vector<Vector3d> vertices = {
      uniqueVertices[0], uniqueVertices[11], uniqueVertices[5],
      uniqueVertices[0], uniqueVertices[5], uniqueVertices[1],
      uniqueVertices[0], uniqueVertices[1], uniqueVertices[7],
      uniqueVertices[0], uniqueVertices[7], uniqueVertices[10],
      uniqueVertices[0], uniqueVertices[10], uniqueVertices[11],

      uniqueVertices[1], uniqueVertices[5], uniqueVertices[9],
      uniqueVertices[5], uniqueVertices[11], uniqueVertices[4],
      uniqueVertices[11], uniqueVertices[10], uniqueVertices[2],
      uniqueVertices[10], uniqueVertices[7], uniqueVertices[6],
      uniqueVertices[7], uniqueVertices[1], uniqueVertices[8],

      uniqueVertices[3], uniqueVertices[9], uniqueVertices[4],
      uniqueVertices[3], uniqueVertices[4], uniqueVertices[2],
      uniqueVertices[3], uniqueVertices[2], uniqueVertices[6],
      uniqueVertices[3], uniqueVertices[6], uniqueVertices[8],
      uniqueVertices[3], uniqueVertices[8], uniqueVertices[9],

      uniqueVertices[4], uniqueVertices[9], uniqueVertices[5],
      uniqueVertices[2], uniqueVertices[4], uniqueVertices[11],
      uniqueVertices[6], uniqueVertices[2], uniqueVertices[10],
      uniqueVertices[8], uniqueVertices[6], uniqueVertices[7],
      uniqueVertices[9], uniqueVertices[8], uniqueVertices[1]
    };

    return vertices;
  }
} // namespace Isaac
