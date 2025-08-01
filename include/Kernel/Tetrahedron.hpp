#ifndef ISAAC_TETRAHEDRON_HPP
#define ISAAC_TETRAHEDRON_HPP

#include <array>
#include <Eigen/Dense>
#include <Kernel/Body.hpp>

using Eigen::Vector3d;
using Eigen::Vector4d;

namespace Isaac {
  class Tetrahedron final : public Body {
  public:
    Tetrahedron() noexcept;

    Tetrahedron(const double &mass_, const std::array<Vector3d, 4> &vertices_, const Vector3d &position_,
                const Vector3d &velocity_, const Vector4d &color_) noexcept;

    Tetrahedron(const Tetrahedron &other) noexcept;

  private:
    static std::vector<Vector3d> constructTetrahedronVertices(const std::array<Vector3d, 4> &vertices_) noexcept;
  };
} // namespace Isaac

#endif // ISAAC_TETRAHEDRON_HPP
