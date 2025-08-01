#include <iostream>
#include <unordered_map>
#include <vector>

#include <Kernel/Constants.hpp>
#include <Kernel/Mesh.hpp>
#include <Kernel/Body.hpp>

using Eigen::Vector3d;
using Eigen::Vector4d;

namespace Isaac {
  Mesh::Mesh() noexcept = default;

  Mesh::Mesh(std::vector<std::unique_ptr<Body> > bodies_) noexcept {
    bodies = std::move(bodies_);
  }

  Body &Mesh::getBody(const std::size_t &index) noexcept {
    return *bodies[index];
  }

  const Body &Mesh::getBody(const std::size_t &index) const noexcept {
    return *bodies[index];
  }

  std::vector<float> Mesh::getVertices(const std::size_t &index) const noexcept {
    const std::size_t vertexCount = bodies[index]->getVertexCount();
    std::vector<float> vertices(3 * vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
      const Vector3d vertex = bodies[index]->getVertex(i);
      vertices[3 * i] = static_cast<float>(vertex.x());
      vertices[3 * i + 1] = static_cast<float>(vertex.y());
      vertices[3 * i + 2] = static_cast<float>(vertex.z());
    }
    return vertices;
  }

  std::size_t Mesh::getSize() const noexcept {
    return bodies.size();
  }

  void Mesh::updateBodies() noexcept {
    const std::size_t n = bodies.size();
    const std::vector<Vector3d> GravitationalAcceleration = getNetGravitationalAcceleration();

#pragma omp parallel for
    for (std::size_t i = 0; i < n; i++) {
      const Vector3d &totalAcceleration = GravitationalAcceleration[i];
      bodies[i]->setAcceleration(totalAcceleration);
      const Vector3d deltaVelocity = bodies[i]->getAcceleration() * TIME_STEP;
      bodies[i]->setVelocity(bodies[i]->getVelocity() + deltaVelocity);
      const Vector3d deltaPosition = bodies[i]->getVelocity() * TIME_STEP + bodies[i]->getAcceleration() * (
                                       TIME_STEP * TIME_STEP * 0.5);
      bodies[i]->setPosition(bodies[i]->getPosition() + deltaPosition);
    }

    const std::unordered_map<std::size_t, std::vector<std::size_t> > collidingBodies = getCollidingBodies();

    for (std::size_t i = 0; i < n; ++i) {
      if (!collidingBodies.contains(i)) { continue; }
      for (const std::size_t &j: collidingBodies.at(i)) {
        Vector3d normal = (bodies[j]->getPosition() - bodies[i]->getPosition()).normalized();

        Vector3d relativeVelocity = bodies[j]->getVelocity() - bodies[i]->getVelocity();
        const float velocityAlongNormal = relativeVelocity.dot(normal);

        if (velocityAlongNormal > 0) return;

        float impulseScalar = -(1 + RESTITUTION_COEFFICIENT) * velocityAlongNormal;
        impulseScalar /= (1.0 / bodies[i]->getMass() + 1.0 / bodies[j]->getMass());

        Vector3d impulse = normal * impulseScalar;
        bodies[i]->setVelocity(bodies[i]->getVelocity() - impulse * (1 / bodies[i]->getMass()));
        bodies[j]->setVelocity(bodies[j]->getVelocity() + impulse * (1 / bodies[j]->getMass()));
      }
    }
  }


  std::vector<Vector3d> Mesh::getNetGravitationalAcceleration() const noexcept {
    const std::size_t n = bodies.size();
    std::vector<Vector3d> GravitationalAcceleration(n, {0, 0, 0});

#pragma omp parallel for
    for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t j = 0; j < n; ++j) {
        if (i == j) { continue; }
        Vector3d positionVector = bodies[j]->getPosition() - bodies[i]->getPosition();
        const float ForceMagnitude = GRAVITATIONAL_CONSTANT * bodies[j]->getMass() / positionVector.squaredNorm();
        GravitationalAcceleration[i] += positionVector.normalized() * ForceMagnitude;
      }
    }
    return GravitationalAcceleration;
  }

  std::unordered_map<std::size_t, std::vector<std::size_t> > Mesh::getCollidingBodies() const noexcept {
    const std::size_t n = bodies.size();
    std::unordered_map<std::size_t, std::vector<std::size_t> > collidingBodies;

#pragma omp parallel for
    for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t j = 0; j < n; ++j) {
        if (i == j) { continue; }

        const float radius_i = (bodies[i]->getVertex(1)).norm();
        const float radius_j = (bodies[j]->getVertex(1)).norm();
        if ((bodies[i]->getPosition() - bodies[j]->getPosition()).norm() <= (radius_i + radius_j)) {
          collidingBodies[i].push_back(j);
        }
      }
    }
    return collidingBodies;
  }
} // namespace Isaac
