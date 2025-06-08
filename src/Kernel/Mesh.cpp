#include <vector>
#include <iostream>
#include <unordered_map>
#include <Kernel/Constants.hpp>
#include <Kernel/Polygon.hpp>
#include <Kernel/Mesh.hpp>

namespace Isaac {
  Mesh::Mesh() noexcept = default;

  Mesh::Mesh(const std::vector<Polygon *> &polygons_) noexcept {
    polygons = polygons_;
  }

  Polygon *Mesh::getBody(const std::size_t &index) const noexcept {
    return polygons[index];
  }

  std::vector<double> Mesh::getVertices(const std::size_t &index) const noexcept {
    const std::size_t vertexCount = polygons[index]->getVertexCount();
    std::vector<double> vertices(3 * vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
      const Vector vertex = polygons[index]->getVertex(i);
      vertices[3 * i] = vertex.getX();
      vertices[3 * i + 1] = vertex.getY();
      vertices[3 * i + 2] = vertex.getZ();
    }
    return vertices;
  }


  std::size_t Mesh::getSize() const noexcept {
    return polygons.size();
  }

  void Mesh::updateBodies() const noexcept {
    const std::size_t n = polygons.size();
    const std::vector<Vector> GravitationalAcceleration = getNetGravitationalAcceleration();

    for (std::size_t i = 0; i < n; i++) {
      const Vector &totalAcceleration = GravitationalAcceleration[i];
      polygons[i]->setAcceleration(totalAcceleration);
      const Vector deltaVelocity = polygons[i]->getAcceleration() * TIME_STEP;
      polygons[i]->setVelocity(polygons[i]->getVelocity() + deltaVelocity);
      const Vector deltaPosition = polygons[i]->getVelocity() * TIME_STEP + polygons[i]->getAcceleration() * (
                                     TIME_STEP * TIME_STEP * 0.5);
      polygons[i]->setPosition(polygons[i]->getPosition() + deltaPosition);
    }

    const std::unordered_map<std::size_t, std::vector<std::size_t> > collidingBodies = getCollidingBodies();

    std::unordered_map<std::size_t, Vector> netMomentum;
    std::unordered_map<std::size_t, double> totalMass;
    for (std::size_t i = 0; i < n; ++i) {
      if (!collidingBodies.contains(i)) { continue; }
      netMomentum[i] = {0, 0, 0};
      totalMass[i] = 0;
      for (const std::size_t &j: collidingBodies.at(i)) {
        netMomentum[i] += polygons[j]->getVelocity() * polygons[j]->getMass();
        totalMass[i] += polygons[j]->getMass();
      }
    }

    for (std::size_t i = 0; i < n; ++i) {
      if (!netMomentum.contains(i)) { continue; }
      polygons[i]->setVelocity(netMomentum.at(i) * ((1.0 - dampingFactor) / totalMass.at(i)));
    }
  }


  std::vector<Vector> Mesh::getNetGravitationalAcceleration() const noexcept {
    const std::size_t n = polygons.size();
    std::vector<Vector> GravitationalAcceleration(n, {0, 0, 0});

    for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t j = 0; j < n; ++j) {
        if (i == j) { continue; }
        Vector positionVector = polygons[j]->getPosition() - polygons[i]->getPosition();
        const double ForceMagnitude = GRAVITATIONAL_CONSTANT * polygons[j]->getMass() / positionVector.squaredNorm();
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

        const double radius_i = (polygons[i]->getVertex(1) - polygons[i]->getPosition()).norm();
        const double radius_j = (polygons[j]->getVertex(1) - polygons[j]->getPosition()).norm();
        if ((polygons[i]->getPosition() - polygons[j]->getPosition()).norm() <= (radius_i + radius_j)) {
          collidingBodies[i].push_back(j);
        }
      }
    }
    return collidingBodies;
  }
} // namespace Isaac
