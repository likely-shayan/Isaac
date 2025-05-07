#include "Kernel/RigidBody2D.hpp"

#include <Kernel/Circle.hpp>

namespace Isaac::Kernel {
RigidBody2D::RigidBody2D() noexcept = default;

RigidBody2D::RigidBody2D(const double &mass_, const Curve2D &curve_) noexcept
    : mass(mass_)
    , curve(curve_) {}

RigidBody2D::RigidBody2D(const double &mass_, const Circle &circle_) noexcept
    : mass(mass_)
    , curve(static_cast<Curve2D>(circle_))
    , circle(circle_) {}

RigidBody2D::RigidBody2D(const double &mass_, const Polygon &polygon_) noexcept
    : mass(mass_)
    , curve(static_cast<Curve2D>(polygon_))
    , polygon(polygon_) {}

RigidBody2D::RigidBody2D(const RigidBody2D &rigidBody2D_) noexcept
    : RigidBody2D(rigidBody2D_.getMass(), rigidBody2D_.getCurve()) {}

CurveType2D RigidBody2D::getCurveType() const noexcept {
  return curve.getCurveType();
}

Curve2D RigidBody2D::getCurve() const noexcept { return curve; }

Vector2d RigidBody2D::getPosition() const noexcept {
  return curve.getPosition();
}

void RigidBody2D::setPosition(const Vector2d &newPosition) noexcept {
  curve.setPosition(newPosition);
  switch (getCurveType()) {
  case CircleType:  circle.setPosition(newPosition); break;
  case PolygonType: polygon.setPosition(newPosition); break;
  }
}

Vector2d RigidBody2D::getVelocity() const noexcept {
  return curve.getVelocity();
}

void RigidBody2D::setVelocity(const Vector2d &newVelocity) noexcept {
  curve.setVelocity(newVelocity);
  switch (getCurveType()) {
  case CircleType:  circle.setVelocity(newVelocity); break;
  case PolygonType: polygon.setVelocity(newVelocity); break;
  }
}

Vector2d RigidBody2D::getAcceleration() const noexcept {
  return curve.getAcceleration();
}

void RigidBody2D::setAcceleration(const Vector2d &newAcceleration) noexcept {
  curve.setAcceleration(newAcceleration);
  switch (getCurveType()) {
  case CircleType:  circle.setAcceleration(newAcceleration); break;
  case PolygonType: polygon.setAcceleration(newAcceleration); break;
  }
}

double RigidBody2D::getRadius() const noexcept {
  if (getCurveType() == CircleType) { return circle.getRadius(); }
  return NULL;
}

int RigidBody2D::getVertexCount() const noexcept {
  if (getCurveType() == PolygonType) { return polygon.getVertexCount(); }
  return NULL;
}

Vector2d RigidBody2D::getVertex(const int &n) const noexcept {
  if (getCurveType() == PolygonType) { return polygon.getVertex(n); }
  return {NULL, NULL};
}

void RigidBody2D::setVertex(const int &n, const Vector2d &newVertex) noexcept {
  if (getCurveType() == PolygonType) { polygon.setVertex(n, newVertex); }
}

std::vector<Vector2d> RigidBody2D::getVertices() const noexcept {
  if (getCurveType() == PolygonType) { return polygon.getVertices(); }
  return {
      {NULL, NULL}
  };
}

void RigidBody2D::setVertices(
    const std::vector<Vector2d> &newVertices) noexcept {
  if (getCurveType() == PolygonType) { polygon.setVertices(newVertices); }
}

double RigidBody2D::getMass() const noexcept { return mass; }
} // namespace Isaac::Kernel
