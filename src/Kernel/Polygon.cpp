#include <vector>
#include <cmath>
#include <numeric>
#include <Kernel/Polygon.hpp>
#include <Kernel/Constants.hpp>

namespace Isaac {
  Polygon::Polygon() noexcept : mass(0) {
  }

  Polygon::Polygon(const double &mass_, const std::vector<Vector> &vertices_, const Vector &position_,
                   const Vector &velocity_, const std::vector<float> &Color_) noexcept {
    mass = mass_;
    vertices = breakVerticesIntoTriangles(vertices_);
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

  Vector Polygon::getVertex(const std::size_t &index) const noexcept {
    return vertices[index] + position;
  }

  std::size_t Polygon::getVertexCount() const noexcept {
    return vertices.size();
  }

  double Polygon::getMass() const {
    return mass;
  }

  Vector Polygon::getPosition() const noexcept {
    return position;
  }

  void Polygon::setPosition(const Vector &position_) noexcept {
    position = position_;
  }

  Vector Polygon::getVelocity() const noexcept {
    return velocity;
  }

  void Polygon::setVelocity(const Vector &velocity_) noexcept {
    velocity = velocity_;
  }

  Vector Polygon::getAcceleration() const noexcept {
    return acceleration;
  }

  void Polygon::setAcceleration(const Vector &acceleration_) noexcept {
    acceleration = acceleration_;
  }

  std::vector<float> Polygon::getColor() const noexcept {
    return Color;
  }

  std::vector<Vector> Polygon::breakVerticesIntoTriangles(const std::vector<Vector> &vertices_) noexcept {
    const std::size_t n = vertices_.size();
    std::vector<Vector> vertices;
    vertices.reserve(3 * (n - 1));
    for (std::size_t i = 0; i < n - 1; ++i) {
      vertices.emplace_back(0, 0, 0);
      vertices.emplace_back(vertices_[i]);
      vertices.emplace_back(vertices_[i + 1]);
    }
    return vertices;
  }

  std::vector<Vector>
  Polygon::constructCircleVertices(const double &radius, const std::size_t &totalVertices) noexcept {
    constexpr double aspectRatio = static_cast<double>(SCREEN_WIDTH) / static_cast<double>(SCREEN_HEIGHT);
    std::vector<Vector> vertices(totalVertices);
    for (std::size_t i = 0; i < totalVertices; ++i) {
      if constexpr (aspectRatio > 1.0) {
        vertices[i] = {radius * std::sin(i * std::numbers::pi / 180), (radius * aspectRatio) * std::cos(i * std::numbers::pi / 180), 0};
      } else {
        vertices[i] = {(radius * aspectRatio) * std::sin(i * std::numbers::pi / 180), radius * std::cos(i * std::numbers::pi / 180), 0};
      }
    }
    return vertices;
  }
} // namespace Isaac
