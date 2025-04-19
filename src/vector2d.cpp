#include "vector2d.hpp"
#include <cmath>

using namespace Issac;

vector2d::vector2d(const float& _x = 0, const float& _y = 0) : x(_x), y(_y) {}

vector2d vector2d::operator+(const vector2d& rhs) const {
  return vector2d(this->x + rhs.x, this->y + rhs.y);
}

float vector2d::magnitude() const {
  return std::sqrt(x*x + y*y);
}

float vector2d::dot(const vector2d& lhs, const vector2d& rhs) {
  return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}