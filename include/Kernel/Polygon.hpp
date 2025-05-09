#ifndef POLYGON_HPP_
#define POLYGON_HPP_

#include <eigen3/Eigen/Dense>
#include <vector>

using Eigen::Vector2f;

namespace Isaac::Kernel
{

  class Polygon {
  public:
    
    Polygon() noexcept;

    Polygon(const int& vertexCount_, const std::vector<Vector2f>& vertices_, const Vector2f& position_, const Vector2f& velocity_, const Vector2f& acceleration_) noexcept;

    Polygon(const Polygon& polygon_) noexcept;

    Vector2f getPosition() const noexcept;

    void setPosition(const Vector2f& newPosition) noexcept;

    Vector2f getVelocity() const noexcept;

    void setVelocity(const Vector2f& newVelocity) noexcept;

    Vector2f getAcceleration() const noexcept;

    void setAcceleration(const Vector2f& newAcceleration) noexcept;

    int getVertexCount() const noexcept;

    Vector2f getVertex(const int& n) const noexcept;

    void setVertex(const int& n, const Vector2f& newVertex) noexcept;

    std::vector<Vector2f> getVertices() const noexcept;

    void setVertices(const std::vector<Vector2f>& newVertices) noexcept;

  private:
    Vector2f position;
    Vector2f velocity;
    Vector2f acceleration;
    int vertexCount;
    std::vector<Vector2f> vertices;
  };
  
} // namespace Isaac::Kernel


#endif // POLYGON_HPP_