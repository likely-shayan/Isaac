#ifndef ISAAC_MESH_HPP
#define ISAAC_MESH_HPP

#include <memory>
#include <unordered_map>
#include <vector>

#include <Eigen/Dense>

#include <Kernel/Polygon.hpp>

using Eigen::Vector3d;
using Eigen::Vector4d;

namespace Isaac {
  class Mesh {
  public:
    Mesh() noexcept;

    explicit Mesh(const std::vector<std::shared_ptr<Polygon> > &polygons_) noexcept;

    [[nodiscard]] std::shared_ptr<Polygon> getBody(const std::size_t &index) const noexcept;

    [[nodiscard]] std::vector<float> getVertices(const std::size_t &index) const noexcept;

    [[nodiscard]] std::size_t getSize() const noexcept;

    void updateBodies() const noexcept;

    [[nodiscard]] std::vector<Vector3d> getNetGravitationalAcceleration() const noexcept;

    [[nodiscard]] std::unordered_map<std::size_t, std::vector<std::size_t> > getCollidingBodies() const noexcept;

  private:
    std::vector<std::shared_ptr<Polygon> > polygons;
  };
} // namespace Isaac

#endif // ISAAC_MESH_HPP
