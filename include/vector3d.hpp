#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

#include <array>
#include <string>

namespace Issac
{
  struct vector3d {
    std::array<float, 3> components;

    vector3d(const float& _x, const float& _y, const float& _z);

    vector3d operator+(const vector3d& rhs) const;

    float magnitude() const;

    static float dot(const vector3d& lhs, const vector3d& rhs);

    static vector3d cross(const vector3d& lhs, const vector3d& rhs);

    std::string print() const;
  };
  
} // namespace Issac


#endif // VECTOR3D_HPP_