#ifndef ISAAC_VECTOR_HPP
#define ISAAC_VECTOR_HPP

#include <istream>
#include <ostream>

namespace Isaac {
  class Vector {
  public:
    Vector() noexcept;

    Vector(const double &x_, const double &y_, const double &z_) noexcept;

    Vector(const Vector &other) noexcept;

    [[nodiscard]] double getX() const noexcept;

    void setX(const double &x_) noexcept;

    [[nodiscard]] double getY() const noexcept;

    void setY(const double &y_) noexcept;

    [[nodiscard]] double getZ() const noexcept;

    void setZ(const double &z_) noexcept;

    Vector operator+(const Vector &other) const noexcept;

    Vector &operator+=(const Vector &other) noexcept;

    Vector operator-(const Vector &other) const noexcept;

    Vector &operator-=(const Vector &other) noexcept;

    Vector operator*(const double &scalar) const noexcept;

    Vector &operator*=(const double &scalar) noexcept;

    [[nodiscard]] double norm() const noexcept;

    [[nodiscard]] double squaredNorm() const noexcept;

    [[nodiscard]] Vector normalized() const noexcept;

    friend std::istream &operator>>(std::istream &is, Vector &vector) noexcept {
      is >> vector.x >> vector.y >> vector.z;
      return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector) noexcept {
      os << "(" << vector.getX() << ", " << vector.getY() << ", " << vector.getZ() << ")";
      return os;
    }

  private:
    double x, y, z;
  };
} // namespace Isaac

#endif // ISAAC_VECTOR_HPP
