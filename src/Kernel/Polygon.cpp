#include "Kernel/Polygon.hpp"

namespace Isaac::Kernel
{
    Polygon::Polygon() noexcept
        : vertexCount(0)
    {
    }

    Polygon::Polygon(const int& vertexCount_,
                     const std::vector<Vector2f>& vertices_,
                     const Vector2f& position_,
                     const Vector2f& velocity_,
                     const Vector2f& acceleration_) noexcept
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

    Vector2f Polygon::getPosition() const noexcept { return position; }

    void Polygon::setPosition(const Vector2f& newPosition) noexcept { position = newPosition; }

    Vector2f Polygon::getVelocity() const noexcept { return velocity; }

    void Polygon::setVelocity(const Vector2f& newVelocity) noexcept { velocity = newVelocity; }

    Vector2f Polygon::getAcceleration() const noexcept { return acceleration; }

    void Polygon::setAcceleration(const Vector2f& newAcceleration) noexcept { acceleration = newAcceleration; }

    int Polygon::getVertexCount() const noexcept { return vertexCount; }

    Vector2f Polygon::getVertex(const int& n) const noexcept { return vertices[n]; }

    void Polygon::setVertex(const int& n, const Vector2f& newVertex) noexcept
    {
        vertices[n] = newVertex;
    }

    std::vector<Vector2f> Polygon::getVertices() const noexcept { return vertices; }

    void Polygon::setVertices(const std::vector<Vector2f>& newVertices) noexcept
    {
        vertices = newVertices;
    }
} // namespace Isaac::Kernel
