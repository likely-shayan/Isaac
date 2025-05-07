#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "Curve3D.hpp"

namespace Isaac::Kernel
{
  
  class Sphere : public Curve3D {
  public:

    Sphere() noexcept;

    Sphere(const double& radius_, const Vector3d& position_, const Vector3d& velocity_, const Vector3d& acceleration_) noexcept;

    Sphere(const Sphere& circle_) noexcept;

    double getRadius() const noexcept;

  private:
    
    double radius;  
  };

} // namespace Isaac::Kernel


#endif // SPHERE_HPP_