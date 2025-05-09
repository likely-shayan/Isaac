#ifndef POLYGON_HPP_
#define POLYGON_HPP_

#include <eigen3/Eigen/Dense>
#include <vector>

using Eigen::Vector2d;

namespace Isaac::Kernel
{

  class Polygon {
  public:
    
    Polygon() noexcept;

    Polygon(const int& vertexCount_, const std::vector<Vector2d>& vertices_, const Vector2d& position_, const Vector2d& velocity_, const Vector2d& acceleration_) noexcept;

    Polygon(const Polygon& polygon_) noexcept;

    Vector2d getPosition() const noexcept;

    void setPosition(const Vector2d& newPosition) noexcept;

    Vector2d getVelocity() const noexcept;

    void setVelocity(const Vector2d& newVelocity) noexcept;

    Vector2d getAcceleration() const noexcept;

    void setAcceleration(const Vector2d& newAcceleration) noexcept;

    int getVertexCount() const noexcept;

    Vector2d getVertex(const int& n) const noexcept;

    void setVertex(const int& n, const Vector2d& newVertex) noexcept;

    std::vector<Vector2d> getVertices() const noexcept;

    void setVertices(const std::vector<Vector2d>& newVertices) noexcept;

  private:
    Vector2d position;
    Vector2d velocity;
    Vector2d acceleration;
    int vertexCount;
    std::vector<Vector2d> vertices;
  };
  
} // namespace Isaac::Kernel


#endif // POLYGON_HPP_