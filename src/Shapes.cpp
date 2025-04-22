#include "Shapes.hpp"
#include "Constants.hpp"
#include "Exceptions.hpp"

namespace Isaac
{
  Shape::Shape(const Vector2f& position_, const Vector2f& direction_, const float& mass_, const ShapeTypes2D& shapeType_) {
    position = position_;
    direction = direction_;
    if (mass_ < 0) throw Isaac::NegativeMassException("Mass of Shape cannot be negative");
    mass = mass_;
    shapeType = shapeType_;
  }

  Shape::Shape(const Shape&& shape_) noexcept : Shape(shape_.getPositionVector(), shape_.getDirectionVector(), shape_.getMass(), shape_.getShapeType()) {}

  void Shape::setPositionVector(const Vector2f& position_) noexcept {position = position_;}

  Vector2f Shape::getPositionVector() const noexcept {return position;}

  void Shape::setDirectionVector(const Vector2f& direction_) noexcept {direction = direction_;}

  Vector2f Shape::getDirectionVector() const noexcept {return direction;}

  float Shape::getMass() const noexcept {return mass;}

  ShapeTypes2D Shape::getShapeType() const noexcept {return shapeType;}

  bool Shape::isMassive() const noexcept {return (mass - MASS_PRECISION) > 0;}

}; // namespace Issac