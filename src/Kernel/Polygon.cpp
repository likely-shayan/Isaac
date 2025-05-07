#include "Kernel/Polygon.hpp"

namespace Isaac::Kernel {
Polygon::Polygon() noexcept = default;

Polygon::Polygon(const int &vertexCount_,
                 const std::vector<Vector2d> &vertices_,
                 const Vector2d &position_,
                 const Vector2d &velocity_,
                 const Vector2d &acceleration_) noexcept
    : Curve2D(PolygonType, position_, velocity_, acceleration_) {
  vertexCount = vertexCount_;
  vertices = vertices_;
}

Polygon::Polygon(const Polygon &polygon_) noexcept
    : Polygon(polygon_.getVertexCount(),
              polygon_.getVertices(),
              polygon_.getPosition(),
              polygon_.getVelocity(),
              polygon_.getAcceleration()) {}

int Polygon::getVertexCount() const noexcept { return vertexCount; }

Vector2d Polygon::getVertex(const int &n) const noexcept { return vertices[n]; }

void Polygon::setVertex(const int &n, const Vector2d &newVertex) noexcept {
  vertices[n] = newVertex;
}

std::vector<Vector2d> Polygon::getVertices() const noexcept { return vertices; }

void Polygon::setVertices(const std::vector<Vector2d> &newVertices) noexcept {
  vertices = newVertices;
}
} // namespace Isaac::Kernel
