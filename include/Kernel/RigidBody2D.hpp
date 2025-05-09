#ifndef RIGID_BODY_2D_HPP_
#define RIGID_BODY_2D_HPP_

#include "Polygon.hpp"

namespace Isaac::Kernel {

    class RigidBody2D {
      public:
        RigidBody2D() noexcept;

        RigidBody2D(const double& mass_, const Polygon& polygon_) noexcept;

        RigidBody2D(const RigidBody2D& rigidBody2D_) noexcept;

        Polygon getPolygon() const noexcept;

        Vector2f getPosition() const noexcept;

        void setPosition(const Vector2f& newPosition) noexcept;

        Vector2f getVelocity() const noexcept;

        void setVelocity(const Vector2f& newVelocity) noexcept;

        Vector2f getAcceleration() const noexcept;

        void setAcceleration(const Vector2f& newAcceleration) noexcept;

        int getVertexCount() const noexcept;

        Vector2f getVertex(const int& n) const noexcept;

        void setVertex(const int& n, const Vector2f& newVertex) noexcept;

        std::vector<Vector2f> getVertices() const noexcept;

        void setVertices(const std::vector<Vector2f>& newVertices) noexcept;

        double getMass() const noexcept;

      private:
        double mass;
        Polygon polygon;
    };

} // namespace Isaac::Kernel

#endif // RIGID_BODY_2D_HPP_
