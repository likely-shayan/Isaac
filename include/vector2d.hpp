#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_

namespace Issac
{
  struct vector2d {
    
    float x, y;

    vector2d(const float& _x, const float& _y);

    vector2d operator+(const vector2d& rhs) const;

    float magnitude() const;

    static float dot(const vector2d& lhs, const vector2d& rhs);
  };
  
} // namespace Issac


#endif // VECTOR2D_HPP_