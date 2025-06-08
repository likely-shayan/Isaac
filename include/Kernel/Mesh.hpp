#ifndef ISAAC_MESH_HPP
#define ISAAC_MESH_HPP

#include <vector>
#include <unordered_map>
#include <Kernel/Vector.hpp>
#include <Kernel/Polygon.hpp>

namespace Isaac {
  class Mesh {
  public:
    Mesh() noexcept;

    explicit Mesh(const std::vector<Polygon *> &polygons_) noexcept;

    [[nodiscard]] Polygon *getBody(const std::size_t &index) const noexcept;

    [[nodiscard]] std::vector<double> getVertices(const std::size_t &index) const noexcept;

    [[nodiscard]] std::size_t getSize() const noexcept;

    void updateBodies() const noexcept;

    [[nodiscard]] std::vector<Vector> getNetGravitationalAcceleration() const noexcept;

    [[nodiscard]] std::unordered_map<std::size_t, std::vector<std::size_t> > getCollidingBodies() const noexcept;

  private:
    double dampingFactor = 0.0;
    std::vector<Polygon *> polygons;
  };
} // namespace Isaac

#endif // ISAAC_MESH_HPP
