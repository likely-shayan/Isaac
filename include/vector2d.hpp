#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_

#include <array>
#include <string>

namespace Issac
{
  struct vector2d {
    std::array<float, 2> components;

    vector2d();

    vector2d(const float& _x, const float& _y);

    vector2d(const vector2d&& other);

    vector2d operator+(const vector2d& rhs) const;

    vector2d operator-(const vector2d& rhs) const;

    vector2d operator*(const float& scalar) const;

    vector2d operator/(const float& scalar) const;

    float magnitude() const;

    static float dot(const vector2d& lhs, const vector2d& rhs);

    std::string print() const;
  };
  
} // namespace Issac


#endif // VECTOR2D_HPP_