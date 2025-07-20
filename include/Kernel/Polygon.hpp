#ifndef ISAAC_POLYGON_HPP
#define ISAAC_POLYGON_HPP

#include <vector>

#include <Eigen/Dense>

using Eigen::Vector3d;
using Eigen::Vector4d;

namespace Isaac {
  class Polygon {
  public:
    Polygon() noexcept;

    Polygon(const float &mass_, const std::vector<Vector3d> &vertices_, const Vector3d &position_,
            const Vector3d &velocity_,
            const Vector4d &Color_) noexcept;

    Polygon(const Polygon &other) noexcept;

    [[nodiscard]] Vector3d getVertex(const std::size_t &index) const noexcept;

    [[nodiscard]] std::size_t getVertexCount() const noexcept;

    [[nodiscard]] float getMass() const;

    [[nodiscard]] Vector3d getPosition() const noexcept;

    void setPosition(const Vector3d &position_) noexcept;

    [[nodiscard]] Vector3d getVelocity() const noexcept;

    void setVelocity(const Vector3d &velocity_) noexcept;

    [[nodiscard]] Vector3d getAcceleration() const noexcept;

    void setAcceleration(const Vector3d &acceleration_) noexcept;

    [[nodiscard]] Vector4d getColor() const noexcept;

    static std::vector<Vector3d> breakVerticesIntoTriangles(const std::vector<Vector3d> &vertices_) noexcept;

    static std::vector<Vector3d> constructCircleVertices(const double &radius,
                                                         const std::size_t &totalVertices = 360) noexcept;

  private:
    double mass;
    std::vector<Vector3d> vertices;
    Vector3d position;
    Vector3d velocity;
    Vector3d acceleration;
    Vector4d Color;
  };
} // namespace Isaac

#endif // ISAAC_POLYGON_HPP
