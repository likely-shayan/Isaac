#include "vector3d.hpp"
#include <cmath>

using namespace Issac;

vector3d::vector3d(const float& _x = 0, const float& _y = 0, const float& _z = 0) : components{_x, _y, _z} {}

vector3d vector3d::operator+(const vector3d& rhs) const {
  return vector3d(
    this->components[0] + rhs.components[0],
    this->components[1] + rhs.components[1],
    this->components[2] + rhs.components[2]
  );
}

float vector3d::magnitude() const {
  return std::sqrt(this->components[0]*this->components[0] + this->components[1]*this->components[1] + this->components[2]*this->components[2]);
}

float vector3d::dot(const vector3d& lhs, const vector3d& rhs) {
  return (lhs.components[0] * rhs.components[0]) + (lhs.components[1] * rhs.components[1]) + (lhs.components[2] * rhs.components[2]);
}

vector3d vector3d::cross(const vector3d& lhs, const vector3d& rhs) {
  return vector3d(
    lhs.components[1]*rhs.components[2] - lhs.components[2]*rhs.components[1],
    lhs.components[2]*rhs.components[0] - lhs.components[0]*rhs.components[2],
    lhs.components[0]*rhs.components[1] - lhs.components[1]*rhs.components[0]
  );
}

std::string vector3d::print() const {
  return "(" + std::to_string(this->components[0]) + "," + std::to_string(this->components[1]) + "," + std::to_string(this->components[2]) + ")";
}