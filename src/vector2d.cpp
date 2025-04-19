#include "vector2d.hpp"
#include <cmath>

using namespace Issac;

vector2d::vector2d(const float& _x = 0, const float& _y = 0) : components{_x, _y} {}

vector2d vector2d::operator+(const vector2d& rhs) const {
  return vector2d(
    this->components[0] + rhs.components[1],
    this->components[0] + rhs.components[1]
  );
}

float vector2d::magnitude() const {
  return std::sqrt(this->components[0]*this->components[0] + this->components[1]*this->components[1]);
}

float vector2d::dot(const vector2d& lhs, const vector2d& rhs) {
  return (lhs.components[0] * rhs.components[0]) + (lhs.components[1] * rhs.components[1]);
}

std::string vector2d::print() const {
  return "(" + std::to_string(this->components[0]) + "," + std::to_string(this->components[1]) + ")";
}