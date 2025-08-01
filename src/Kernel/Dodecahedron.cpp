#include <Kernel/Dodecahedron.hpp>

namespace Isaac {
  Dodecahedron::Dodecahedron() noexcept = default;

  Dodecahedron::Dodecahedron(const double &mass_, const double &radius_, const Vector3d &position_,
                             const Vector3d &velocity_, const Vector4d &color_) noexcept : Body(
    mass_, constructDodecahedronVertices(radius_), position_, velocity_, color_) {
  }

  Dodecahedron::Dodecahedron(const Dodecahedron &other) noexcept = default;

  std::vector<Vector3d> Dodecahedron::constructDodecahedronVertices(const double &radius_) noexcept {
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    const double invphi = 1.0 / phi;

    std::array uniqueVertices = {
      Vector3d(-1, -1, -1), Vector3d(-1, -1, 1), Vector3d(-1, 1, -1), Vector3d(-1, 1, 1),
      Vector3d(1, -1, -1), Vector3d(1, -1, 1), Vector3d(1, 1, -1), Vector3d(1, 1, 1),
      Vector3d(0, -invphi, -phi), Vector3d(0, -invphi, phi), Vector3d(0, invphi, -phi), Vector3d(0, invphi, phi),
      Vector3d(-invphi, -phi, 0), Vector3d(-invphi, phi, 0), Vector3d(invphi, -phi, 0), Vector3d(invphi, phi, 0),
      Vector3d(-phi, 0, -invphi), Vector3d(-phi, 0, invphi), Vector3d(phi, 0, -invphi), Vector3d(phi, 0, invphi)
    };

    const double scale = radius_ / std::sqrt(3.0);
    for (auto &v: uniqueVertices) {
      v *= scale;
    }

    const int faces[12][5] = {
      {1, 9, 11, 3, 17}, {0, 8, 10, 2, 16}, {5, 14, 12, 0, 16}, {4, 18, 6, 2, 10},
      {7, 19, 5, 1, 11}, {3, 13, 15, 7, 11}, {0, 12, 1, 9, 8}, {2, 13, 3, 17, 16},
      {6, 15, 7, 19, 18}, {4, 14, 5, 19, 18}, {8, 9, 1, 5, 14}, {10, 8, 12, 14, 4}
    };

    std::vector<Vector3d> vertices;
    vertices.reserve(12 * 3 * 3);

    for (int i = 0; i < 12; ++i) {
      const Vector3d &v0 = uniqueVertices[faces[i][0]];
      const Vector3d &v1 = uniqueVertices[faces[i][1]];
      const Vector3d &v2 = uniqueVertices[faces[i][2]];
      const Vector3d &v3 = uniqueVertices[faces[i][3]];
      const Vector3d &v4 = uniqueVertices[faces[i][4]];

      vertices.push_back(v0);
      vertices.push_back(v1);
      vertices.push_back(v2);

      vertices.push_back(v0);
      vertices.push_back(v2);
      vertices.push_back(v3);

      vertices.push_back(v0);
      vertices.push_back(v3);
      vertices.push_back(v4);
    }

    return vertices;
  }
} // namespace Isaac
