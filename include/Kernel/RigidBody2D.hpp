#ifndef RIGID_BODY_2D_H
#define RIGID_BODY_2D_H

#include "Curve2D.hpp"
#include "Circle.hpp"
#include "Polygon.hpp"

namespace Isaac::Kernel {

    class RigidBody2D {
      public:
        RigidBody2D() noexcept;

        RigidBody2D(const double& mass_, const Curve2D& curve_) noexcept;

        RigidBody2D(const double& mass_, const Circle& circle_) noexcept;

        RigidBody2D(const double& mass_, const Polygon& polygon_) noexcept;

        RigidBody2D(const RigidBody2D& rigidBody2D_) noexcept;

        CurveType2D getCurveType() const noexcept;

        Curve2D getCurve() const noexcept;

        Vector2d getPosition() const noexcept;

        void setPosition(const Vector2d& newPosition) noexcept;

        Vector2d getVelocity() const noexcept;

        void setVelocity(const Vector2d& newVelocity) noexcept;

        Vector2d getAcceleration() const noexcept;

        void setAcceleration(const Vector2d& newAcceleration) noexcept;

        double getRadius() const noexcept;

        int getVertexCount() const noexcept;

        Vector2d getVertex(const int& n) const noexcept;

        void setVertex(const int& n, const Vector2d& newVertex) noexcept;

        std::vector<Vector2d> getVertices() const noexcept;

        void setVertices(const std::vector<Vector2d>& newVertices) noexcept;

        double getMass() const noexcept;

      private:
        double mass;
        Curve2D curve;
        Circle circle;
        Polygon polygon;
    };

} // namespace Isaac::Kernel

#endif // RIGID_BODY_2D_H
