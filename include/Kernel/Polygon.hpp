#ifndef POLYGON_HPP_
#define POLYGON_HPP_

#include "Curve2D.hpp"
#include <vector>

namespace Isaac::Kernel
{

  class Polygon : public Curve2D {
  public:
    
    Polygon() noexcept;

    Polygon(const int& vertexCount_, const std::vector<Vector2d>& vertices_, const Vector2d& position_, const Vector2d& velocity_, const Vector2d& acceleration_) noexcept;

    Polygon(const Polygon& polygon_) noexcept;

    int getVertexCount() const noexcept;

    Vector2d getVertex(const int& n) const noexcept;

    void setVertex(const int& n, const Vector2d& newVertex) noexcept;

    std::vector<Vector2d> getVertices() const noexcept;

    void setVertices(const std::vector<Vector2d>& newVertices) noexcept;

  private:
    
    int vertexCount;

    std::vector<Vector2d> vertices;
  };
  
} // namespace Isaac::Kernel


#endif // POLYGON_HPP_