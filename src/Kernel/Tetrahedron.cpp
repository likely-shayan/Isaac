#include <Kernel/Tetrahedron.hpp>

namespace Isaac {
  Tetrahedron::Tetrahedron() noexcept = default;

  Tetrahedron::Tetrahedron(const double &mass_, const std::array<Vector3d, 4> &vertices_, const Vector3d &position_,
                           const Vector3d &velocity_, const Vector4d &color_) noexcept : Body(
    mass_, constructTetrahedronVertices(vertices_), position_, velocity_, color_) {
  }

  Tetrahedron::Tetrahedron(const Tetrahedron &other) noexcept = default;

  std::vector<Vector3d> Tetrahedron::constructTetrahedronVertices(const std::array<Vector3d, 4> &vertices_) noexcept {
    std::vector<Vector3d> vertices(12);

    vertices[0] = vertices_[0];
    vertices[1] = vertices_[1];
    vertices[2] = vertices_[2];

    vertices[3] = vertices_[0];
    vertices[4] = vertices_[2];
    vertices[5] = vertices_[3];

    vertices[6] = vertices_[0];
    vertices[7] = vertices_[3];
    vertices[8] = vertices_[1];

    vertices[9] = vertices_[1];
    vertices[10] = vertices_[3];
    vertices[11] = vertices_[2];

    return vertices;
  }
} // namespace Isaac
