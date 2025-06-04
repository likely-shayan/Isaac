#include <vector>
#include <Kernel/Polygon.hpp>

namespace Isaac {
  Polygon::Polygon() noexcept : mass(0), Color({0, 0, 0, 0}) {
  }

  Polygon::Polygon(const double &mass_, const std::vector<Vector> &vertices_, const Vector &position_,
                   const Vector &velocity_, const Vector &acceleration_, const std::array<float, 4> &Color_) noexcept {
    mass = mass_;
    vertices = breakVerticesIntoTriangles(position_, vertices_);
    position = position_;
    velocity = velocity_;
    acceleration = acceleration_;
    Color = Color_;
  }

  Polygon::Polygon(const Polygon &other) noexcept {
    mass = other.mass;
    vertices = other.vertices;
    position = other.position;
    velocity = other.velocity;
    acceleration = other.acceleration;
    Color = other.getColor();
  }

  Vector Polygon::getVertex(const int &index) const noexcept {
    return vertices[index] + position;
  }

  int Polygon::getVertexCount() const noexcept {
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

  std::array<float, 4> Polygon::getColor() const noexcept {
    return Color;
  }

  std::vector<Vector> Polygon::breakVerticesIntoTriangles(const Vector &center_,
                                                          const std::vector<Vector> &vertices_) noexcept {
    const std::size_t n = vertices_.size();
    std::vector<Vector> vertices(3 * n);
    for (std::size_t i = 0; i < n; ++i) {
      vertices.push_back(center_);
      vertices.push_back(vertices_[3 * i % n]);
      vertices.push_back(vertices_[(3 * i + 1) % n]);
    }
    return vertices;
  }
} // namespace Isaac
