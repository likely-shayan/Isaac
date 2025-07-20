#include <iostream>
#include <unordered_map>
#include <vector>

#include <Kernel/Constants.hpp>
#include <Kernel/Mesh.hpp>
#include <Kernel/Polygon.hpp>

using Eigen::Vector3d;
using Eigen::Vector4d;

namespace Isaac {
  Mesh::Mesh() noexcept = default;

  Mesh::Mesh(const std::vector<std::shared_ptr<Polygon> > &polygons_) noexcept {
    polygons = polygons_;
  }

  std::shared_ptr<Polygon> Mesh::getBody(const std::size_t &index) const noexcept {
    return polygons[index];
  }

  std::vector<float> Mesh::getVertices(const std::size_t &index) const noexcept {
    const std::size_t vertexCount = polygons[index]->getVertexCount();
    std::vector<float> vertices(3 * vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
      const Vector3d vertex = polygons[index]->getVertex(i);
      vertices[3 * i] = static_cast<float>(vertex.x());
      vertices[3 * i + 1] = static_cast<float>(vertex.y());
      vertices[3 * i + 2] = static_cast<float>(vertex.z());
    }
    return vertices;
  }

  std::size_t Mesh::getSize() const noexcept {
    return polygons.size();
  }

  void Mesh::updateBodies() const noexcept {
    const std::size_t n = polygons.size();
    const std::vector<Vector3d> GravitationalAcceleration = getNetGravitationalAcceleration();

    for (std::size_t i = 0; i < n; i++) {
      const Vector3d &totalAcceleration = GravitationalAcceleration[i];
      polygons[i]->setAcceleration(totalAcceleration);
      const Vector3d deltaVelocity = polygons[i]->getAcceleration() * TIME_STEP;
      polygons[i]->setVelocity(polygons[i]->getVelocity() + deltaVelocity);
      const Vector3d deltaPosition = polygons[i]->getVelocity() * TIME_STEP + polygons[i]->getAcceleration() * (
                                       TIME_STEP * TIME_STEP * 0.5);
      polygons[i]->setPosition(polygons[i]->getPosition() + deltaPosition);
    }

    const std::unordered_map<std::size_t, std::vector<std::size_t> > collidingBodies = getCollidingBodies();

    for (std::size_t i = 0; i < n; ++i) {
      if (!collidingBodies.contains(i)) { continue; }
      for (const std::size_t &j: collidingBodies.at(i)) {
        Vector3d normal = (polygons[j]->getPosition() - polygons[i]->getPosition()).normalized();

        Vector3d relativeVelocity = polygons[j]->getVelocity() - polygons[i]->getVelocity();
        const float velocityAlongNormal = relativeVelocity.dot(normal);

        if (velocityAlongNormal > 0) return;

        float impulseScalar = -(1 + RESTITUTION_COEFFICIENT) * velocityAlongNormal;
        impulseScalar /= (1.0 / polygons[i]->getMass() + 1.0 / polygons[j]->getMass());

        Vector3d impulse = normal * impulseScalar;
        polygons[i]->setVelocity(polygons[i]->getVelocity() - impulse * (1 / polygons[i]->getMass()));
        polygons[j]->setVelocity(polygons[j]->getVelocity() + impulse * (1 / polygons[j]->getMass()));
      }
    }
  }


  std::vector<Vector3d> Mesh::getNetGravitationalAcceleration() const noexcept {
    const std::size_t n = polygons.size();
    std::vector<Vector3d> GravitationalAcceleration(n, {0, 0, 0});

    for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t j = 0; j < n; ++j) {
        if (i == j) { continue; }
        Vector3d positionVector = polygons[j]->getPosition() - polygons[i]->getPosition();
        const float ForceMagnitude = GRAVITATIONAL_CONSTANT * polygons[j]->getMass() / positionVector.squaredNorm();
        GravitationalAcceleration[i] += positionVector.normalized() * ForceMagnitude;
      }
    }
    return GravitationalAcceleration;
  }

  std::unordered_map<std::size_t, std::vector<std::size_t> > Mesh::getCollidingBodies() const noexcept {
    const std::size_t n = polygons.size();
    std::unordered_map<std::size_t, std::vector<std::size_t> > collidingBodies;

    for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t j = 0; j < n; ++j) {
        if (i == j) { continue; }

        const float radius_i = (polygons[i]->getVertex(1)).norm();
        const float radius_j = (polygons[j]->getVertex(1)).norm();
        if ((polygons[i]->getPosition() - polygons[j]->getPosition()).norm() <= (radius_i + radius_j)) {
          collidingBodies[i].push_back(j);
        }
      }
    }
    return collidingBodies;
  }
} // namespace Isaac
