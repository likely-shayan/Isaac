#include "Kernel/Shapes.hpp"
#include "Kernel/Constants.hpp"
#include "Kernel/Exceptions.hpp"

namespace Isaac
{
  Shape::Shape(const Vector2f& position_,const float& mass_, const ShapeTypes2D& shapeType_) {
    position = position_;
    if (mass_ < 0) throw Isaac::NegativeMassException("Mass of Shape cannot be negative");
    mass = mass_;
    shapeType = shapeType_;
    switch (shapeType_) {
      case ShapeTypes2D::Circle:
        shapeType = ShapeTypes2D::Circle;
        break;
      default:
        throw Isaac::UnknownShapeTypeException("Could not deduce Shape Type");
    }
  }

  // Shape::Shape(const Shape&& shape_) noexcept : Shape(shape_.getPositionVector(), shape_.getMass(), shape_.getShapeType()) {}

  void Shape::setPositionVector(const Vector2f& position_) noexcept {position = position_;}

  Vector2f Shape::getPositionVector() const noexcept {return position;}

  float Shape::getMass() const noexcept {return mass;}

  ShapeTypes2D Shape::getShapeType() const noexcept {return shapeType;}

}; // namespace Issac