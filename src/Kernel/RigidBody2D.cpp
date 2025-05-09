#include "Kernel/RigidBody2D.hpp"

namespace Isaac::Kernel
{
    RigidBody2D::RigidBody2D() noexcept = default;

    RigidBody2D::RigidBody2D(const double& mass_, const Polygon& polygon_) noexcept
        : mass(mass_)
          , polygon(polygon_)
    {
    }

    RigidBody2D::RigidBody2D(const RigidBody2D& rigidBody2D_) noexcept
        : RigidBody2D(rigidBody2D_.getMass(), rigidBody2D_.getPolygon())
    {
    }

    Polygon RigidBody2D::getPolygon() const noexcept { return polygon; }

    Vector2f RigidBody2D::getPosition() const noexcept { return polygon.getPosition(); }

    void RigidBody2D::setPosition(const Vector2f& newPosition) noexcept { polygon.setPosition(newPosition); }

    Vector2f RigidBody2D::getVelocity() const noexcept { return polygon.getVelocity(); }

    void RigidBody2D::setVelocity(const Vector2f& newVelocity) noexcept { polygon.setVelocity(newVelocity); }

    Vector2f RigidBody2D::getAcceleration() const noexcept { return polygon.getAcceleration(); }

    void RigidBody2D::setAcceleration(const Vector2f& newAcceleration) noexcept
    {
        polygon.setAcceleration(newAcceleration);
    }

    int RigidBody2D::getVertexCount() const noexcept { return polygon.getVertexCount(); }

    Vector2f RigidBody2D::getVertex(const int& n) const noexcept { return polygon.getVertex(n); }

    void RigidBody2D::setVertex(const int& n, const Vector2f& newVertex) noexcept { polygon.setVertex(n, newVertex); }

    std::vector<Vector2f> RigidBody2D::getVertices() const noexcept { return polygon.getVertices(); }

    void RigidBody2D::setVertices(
        const std::vector<Vector2f>& newVertices) noexcept { polygon.setVertices(newVertices); }

    double RigidBody2D::getMass() const noexcept { return mass; }
} // namespace Isaac::Kernel
