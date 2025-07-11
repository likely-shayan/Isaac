#include <cmath>
#include <Kernel/Vector.hpp>

namespace Isaac {
  Vector::Vector() noexcept : x(0), y(0), z(0) {
  }

  Vector::Vector(const double &x_, const double &y_, const double &z_) noexcept {
    x = x_;
    y = y_;
    z = z_;
  }

  Vector::Vector(const Vector &other) noexcept {
    x = other.x;
    y = other.y;
    z = other.z;
  }

  double Vector::getX() const noexcept {
    return x;
  }

  void Vector::setX(const double &x_) noexcept {
    x = x_;
  }

  double Vector::getY() const noexcept {
    return y;
  }

  void Vector::setY(const double &y_) noexcept {
    y = y_;
  }

  double Vector::getZ() const noexcept {
    return z;
  }

  void Vector::setZ(const double &z_) noexcept {
    z = z_;
  }

  Vector Vector::operator+(const Vector &other) const noexcept {
    return {x + other.x, y + other.y, z + other.z};
  }

  Vector &Vector::operator+=(const Vector &other) noexcept {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  Vector Vector::operator-(const Vector &other) const noexcept {
    return {x - other.x, y - other.y, z - other.z};
  }

  Vector &Vector::operator-=(const Vector &other) noexcept {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  Vector Vector::operator*(const double &scalar) const noexcept {
    return {scalar * x, scalar * y, scalar * z};
  }

  Vector &Vector::operator*=(const double &scalar) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  double Vector::norm() const noexcept {
    return std::hypot(this->x, this->y, this->z);
  }

  double Vector::squaredNorm() const noexcept {
    return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
  }

  Vector Vector::normalized() const noexcept {
    return {this->x / norm(), this->y / norm(), this->z / norm()};
  }

  double Vector::dot(const Vector &a, const Vector &b) noexcept {
    return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
  }
} // namespace Isaac
