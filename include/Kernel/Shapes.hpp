#ifndef SHAPES_HPP_
#define SHAPES_HPP_

#include <eigen3/Eigen/Dense>

using Eigen::Vector2f;

namespace Isaac
{
  enum class ShapeTypes2D {Circle};

  struct Shape
  {
    private:
      ShapeTypes2D shapeType;
      Vector2f position;
      float mass;

    public:

      Shape() noexcept = default;

      Shape(const Vector2f& position_, const float& mass_, const ShapeTypes2D& shapeType_);
    
      // Shape(const Shape&& shape_) noexcept;

      void setPositionVector(const Vector2f& position_) noexcept;
      Vector2f getPositionVector() const noexcept;

      float getMass() const noexcept;

      ShapeTypes2D getShapeType() const noexcept;
  };
} // namespace Isaac

#endif // SHAPES_HPP_