#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include "Curve2D.hpp"

namespace Isaac::Kernel {

  class Circle : public Curve2D {
  public:

    Circle() noexcept;

    Circle(const double& radius_, const Vector2d& position_, const Vector2d& velocity_, const Vector2d& acceleration_) noexcept;

    Circle(const Circle& circle_) noexcept;

    double getRadius() const noexcept;

  private:
    
    double radius;
  };

} // namespace Isaac::Kernel

#endif // CIRCLE_HPP_