#ifndef CIRCLE_2D_HPP_
#define CIRCLE_2D_HPP_

#include "Curves2D.hpp"

namespace Isaac::Kernel {

  class Circle2D : public Curve2D {
  public:

    Circle2D() noexcept = default;

    Circle2D(const double& radius_, const Vector2d& position_, const Vector2d& velocity_, const Vector2d& acceleration_) noexcept;

    Circle2D(const Circle2D& circle_) noexcept;

    double getRadius() noexcept;

  private:
    
    double radius;
  };

} // namespace Isaac::Kernel

#endif // CIRCLE_2D_HPP_