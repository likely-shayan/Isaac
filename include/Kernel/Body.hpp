#ifndef ISAAC_BODY_HPP
#define ISAAC_BODY_HPP

#include <vector>

#include <Eigen/Dense>

using Eigen::Vector3d;
using Eigen::Vector4d;

namespace Isaac {
  class Body {
  public:
    Body() noexcept;

    Body(const double &mass_, const std::vector<Vector3d> &vertices_, const Vector3d &position_,
         const Vector3d &velocity_,
         const Vector4d &color_) noexcept;

    Body(const Body &other) noexcept;

    [[nodiscard]] Vector3d getVertex(const std::size_t &index) const noexcept;

    [[nodiscard]] std::size_t getVertexCount() const noexcept;

    [[nodiscard]] double getMass() const;

    [[nodiscard]] Vector3d getPosition() const noexcept;

    void setPosition(const Vector3d &position_) noexcept;

    [[nodiscard]] Vector3d getVelocity() const noexcept;

    void setVelocity(const Vector3d &velocity_) noexcept;

    [[nodiscard]] Vector3d getAcceleration() const noexcept;

    void setAcceleration(const Vector3d &acceleration_) noexcept;

    [[nodiscard]] Vector4d getColor() const noexcept;

    virtual ~Body() = default;

  private:
    double mass;
    std::vector<Vector3d> vertices;
    Vector3d position;
    Vector3d velocity;
    Vector3d acceleration;
    Vector4d color;
  };
} // namespace Isaac

#endif // ISAAC_BODY_HPP
