#include <cmath>
#include <vector>

#include <Kernel/Constants.hpp>
#include <Kernel/Polygon.hpp>

using Eigen::Vector3d;
using Eigen::Vector4d;

namespace Isaac {
  Polygon::Polygon() noexcept : mass(0) {
  }

  Polygon::Polygon(const float &mass_, const std::vector<Vector3d> &vertices_, const Vector3d &position_,
                   const Vector3d &velocity_, const Vector4d &Color_) noexcept {
    mass = mass_;
    vertices = vertices_;
    position = position_;
    velocity = velocity_;
    acceleration = {0, 0, 0};
    Color = Color_;
  }

  Polygon::Polygon(const Polygon &other) noexcept {
    mass = other.mass;
    vertices = other.vertices;
    position = other.position;
    velocity = other.velocity;
    acceleration = other.acceleration;
    Color = other.Color;
  }

  Vector3d Polygon::getVertex(const std::size_t &index) const noexcept {
    return vertices[index];
  }

  std::size_t Polygon::getVertexCount() const noexcept {
    return vertices.size();
  }

  float Polygon::getMass() const {
    return mass;
  }

  Vector3d Polygon::getPosition() const noexcept {
    return position;
  }

  void Polygon::setPosition(const Vector3d &position_) noexcept {
    position = position_;
  }

  Vector3d Polygon::getVelocity() const noexcept {
    return velocity;
  }

  void Polygon::setVelocity(const Vector3d &velocity_) noexcept {
    velocity = velocity_;
  }

  Vector3d Polygon::getAcceleration() const noexcept {
    return acceleration;
  }

  void Polygon::setAcceleration(const Vector3d &acceleration_) noexcept {
    acceleration = acceleration_;
  }

  Vector4d Polygon::getColor() const noexcept {
    return Color;
  }
} // namespace Isaac
