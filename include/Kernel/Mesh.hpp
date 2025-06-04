#ifndef ISAAC_MESH_HPP
#define ISAAC_MESH_HPP

#include <vector>
#include <Kernel/Vector.hpp>
#include <Kernel/Polygon.hpp>

namespace Isaac {
  class Mesh {
  public:
    Mesh() noexcept;

    explicit Mesh(const std::vector<Polygon *> &polygons_) noexcept;

    void addPolygon(Polygon *polygon_) noexcept;

    [[nodiscard]] Polygon *getBody(const int &index) const noexcept;

    [[nodiscard]] std::vector<double> getVertices(const int &index) const noexcept;

    [[nodiscard]] std::size_t getSize() const noexcept;

    void updateBodies() const noexcept;

    [[nodiscard]] std::vector<Vector> getNetGravitationalAcceleration() const noexcept;

  private:
    std::vector<Polygon *> polygons;
  };
} // namespace Isaac

#endif // ISAAC_MESH_HPP
