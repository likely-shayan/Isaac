#include <cmath>
#include <vector>

#include <Kernel/Constants.hpp>
#include <Kernel/Body.hpp>

using Eigen::Vector3d;
using Eigen::Vector4d;

namespace Isaac {
  Body::Body() noexcept : mass(0) {
  }

  Body::Body(const float &mass_, const std::vector<Vector3d> &vertices_, const Vector3d &position_,
             const Vector3d &velocity_, const Vector4d &Color_) noexcept {
    mass = mass_;
    vertices = vertices_;
    position = position_;
    velocity = velocity_;
    acceleration = {0, 0, 0};
    Color = Color_;
  }

  Body::Body(const Body &other) noexcept {
    mass = other.mass;
    vertices = other.vertices;
    position = other.position;
    velocity = other.velocity;
    acceleration = other.acceleration;
    Color = other.Color;
  }

  Vector3d Body::getVertex(const std::size_t &index) const noexcept {
    return vertices[index];
  }

  std::size_t Body::getVertexCount() const noexcept {
    return vertices.size();
  }

  float Body::getMass() const {
    return mass;
  }

  Vector3d Body::getPosition() const noexcept {
    return position;
  }

  void Body::setPosition(const Vector3d &position_) noexcept {
    position = position_;
  }

  Vector3d Body::getVelocity() const noexcept {
    return velocity;
  }

  void Body::setVelocity(const Vector3d &velocity_) noexcept {
    velocity = velocity_;
  }

  Vector3d Body::getAcceleration() const noexcept {
    return acceleration;
  }

  void Body::setAcceleration(const Vector3d &acceleration_) noexcept {
    acceleration = acceleration_;
  }

  Vector4d Body::getColor() const noexcept {
    return Color;
  }
} // namespace Isaac
