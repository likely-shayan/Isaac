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

  const std::vector<Vector3d> &Polygon::getVertices() const noexcept {
    return vertices;
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

  std::vector<Vector3d> Polygon::breakVerticesIntoTriangles(const std::vector<Vector3d> &vertices_) noexcept {
    const std::size_t n = vertices_.size();
    std::vector<Vector3d> vertices;
    vertices.reserve(3 * (n - 1));
    for (std::size_t i = 0; i < n - 1; ++i) {
      vertices.emplace_back(0, 0, 0);
      vertices.emplace_back(vertices_[i]);
      vertices.emplace_back(vertices_[i + 1]);
    }
    return vertices;
  }

  std::vector<Vector3d>
  Polygon::constructCircleVertices(const float &radius, const std::size_t &totalVertices) noexcept {
    constexpr double aspectRatio = static_cast<double>(SCREEN_WIDTH) / static_cast<double>(SCREEN_HEIGHT);
    std::vector<Vector3d> vertices(totalVertices);
    for (std::size_t i = 0; i < totalVertices; ++i) {
      if constexpr (aspectRatio > 1.0) {
        vertices[i] = {radius * std::sin(i * M_PI / 180), (radius * aspectRatio) * std::cos(i * M_PI / 180), 0};
      } else {
        vertices[i] = {(radius * aspectRatio) * std::sin(i * M_PI / 180), radius * std::cos(i * M_PI / 180), 0};
      }
    }
    return vertices;
  }
} // namespace Isaac
