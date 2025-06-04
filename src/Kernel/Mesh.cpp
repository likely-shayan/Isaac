#include <algorithm>
#include <vector>
#include <Kernel/Constants.hpp>
#include <Kernel/Polygon.hpp>
#include <Kernel/Mesh.hpp>

namespace Isaac {
  Mesh::Mesh() noexcept = default;

  Mesh::Mesh(const std::vector<Polygon *> &polygons_) noexcept {
    polygons = polygons_;
  }

  void Mesh::addPolygon(Polygon *polygon_) noexcept {
    polygons.push_back(polygon_);
  }


  Polygon *Mesh::getBody(const int &index) const noexcept {
    return polygons[index];
  }

  std::vector<double> Mesh::getVertices(const int &index) const noexcept {
    const int vertexCount = polygons[index]->getVertexCount();
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
    const std::vector<Vector> GravitationalAcceleration = getNetGravitationalAcceleration();

    for (int i = 0; i < polygons.size(); i++) {
      const Vector &totalAcceleration = GravitationalAcceleration[i];
      polygons[i]->setAcceleration(totalAcceleration);
      const Vector deltaVelocity = totalAcceleration * TIME_STEP;
      polygons[i]->setVelocity(polygons[i]->getVelocity() + deltaVelocity);
      const Vector deltaPosition = polygons[i]->getVelocity() * TIME_STEP + totalAcceleration * (
                                     TIME_STEP * TIME_STEP * 0.5);
      polygons[i]->setPosition(polygons[i]->getPosition() + deltaPosition);
    }
  }


  std::vector<Vector> Mesh::getNetGravitationalAcceleration() const noexcept {
    std::vector<Vector> GravitationalAcceleration(polygons.size(), {0, 0, 0});

    for (int i = 0; i < polygons.size(); ++i) {
      for (int j = 0; j < polygons.size(); ++j) {
        if (i == j) { continue; }
        Vector positionVector = polygons[j]->getPosition() - polygons[i]->getPosition();
        double ForceMagnitude = GRAVITATIONAL_CONSTANT * polygons[j]->getMass() / positionVector.squaredNorm();
        GravitationalAcceleration[i] += positionVector.normalized() * ForceMagnitude;
      }
    }
    return GravitationalAcceleration;
  }
} // namespace Isaac
