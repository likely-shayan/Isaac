#include "vector2d.hpp"
#include "exceptions.hpp"
#include <cmath>

using namespace Isaac;

vector2d::vector2d() : components{0, 0} {}

vector2d::vector2d(const float& _x = 0, const float& _y = 0) : components{_x, _y} {}

vector2d::vector2d(const vector2d&& other) : components(other.components) {}

vector2d vector2d::operator+(const vector2d& rhs) const {
  return vector2d(
    this->components[0] + rhs.components[0],
    this->components[1] + rhs.components[1]
  );
}

vector2d vector2d::operator-(const vector2d& rhs) const {
  return vector2d(
    this->components[0] - rhs.components[0],
    this->components[1] - rhs.components[1]
  );
}

vector2d vector2d::operator*(const float& scalar) const {
  return vector2d(
    scalar * this->components[0],
    scalar* this->components[1]
  );
}

vector2d vector2d::operator/(const float& scalar) const {
  if (scalar == 0) {
    throw Isaac::ZeroDevisionException("Scalar divison of vector2d by 0");
  }
  return vector2d(
    this->components[0]/scalar,
    this->components[1]/scalar
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