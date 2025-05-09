#include "Kernel/Polygon.hpp"

namespace Isaac::Kernel
{
    Polygon::Polygon() noexcept
        : vertexCount(0)
    {
    }

    Polygon::Polygon(const int& vertexCount_,
                     const std::vector<Vector2d>& vertices_,
                     const Vector2d& position_,
                     const Vector2d& velocity_,
                     const Vector2d& acceleration_) noexcept
        : position(position_)
          , velocity(velocity_)
          , acceleration(acceleration_)
          , vertexCount(vertexCount_)
          , vertices(vertices_)
    {
    }

    Polygon::Polygon(const Polygon& polygon_) noexcept
        : Polygon(polygon_.getVertexCount(),
                  polygon_.getVertices(),
                  polygon_.getPosition(),
                  polygon_.getVelocity(),
                  polygon_.getAcceleration())
    {
    }

    Vector2d Polygon::getPosition() const noexcept { return position; }

    void Polygon::setPosition(const Vector2d& newPosition) noexcept { position = newPosition; }

    Vector2d Polygon::getVelocity() const noexcept { return velocity; }

    void Polygon::setVelocity(const Vector2d& newVelocity) noexcept { velocity = newVelocity; }

    Vector2d Polygon::getAcceleration() const noexcept { return acceleration; }

    void Polygon::setAcceleration(const Vector2d& newAcceleration) noexcept { acceleration = newAcceleration; }

    int Polygon::getVertexCount() const noexcept { return vertexCount; }

    Vector2d Polygon::getVertex(const int& n) const noexcept { return vertices[n]; }

    void Polygon::setVertex(const int& n, const Vector2d& newVertex) noexcept
    {
        vertices[n] = newVertex;
    }

    std::vector<Vector2d> Polygon::getVertices() const noexcept { return vertices; }

    void Polygon::setVertices(const std::vector<Vector2d>& newVertices) noexcept
    {
        vertices = newVertices;
    }
} // namespace Isaac::Kernel
