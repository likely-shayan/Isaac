#ifndef MESH_HPP_
#define MESH_HPP_

#include "Shapes.hpp"
#include <vector>

namespace Isaac
{

  class Mesh
  {
    std::vector<Isaac::Shape> shapes;
    std::vector<Vector2f> Velocities;
    int meshSize;

    public:
      Mesh() noexcept = default;

      Mesh(const std::vector<Isaac::Shape>& shapes_) noexcept;

      Mesh(const Mesh&& mesh_) noexcept;

      int getMeshSize() const noexcept;

      std::vector<Isaac::Shape> getShapes() const noexcept;

      Vector2f getPosition(const int& index) const;

      float getMass(const int& index) const;

      Vector2f getNetForce(const int& index) const;

      Vector2f getNetAcceleration(const int& index) const;

      Vector2f getVelocity(const int& index) const;

      void updateVelocity(const int& index);

      void updatePostion(const int& index);
  };

}; // namespace Isaac

#endif // MESH_HPP_