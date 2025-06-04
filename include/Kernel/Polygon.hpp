#ifndef ISAAC_POLYGON_HPP
#define ISAAC_POLYGON_HPP

#include <array>
#include <vector>
#include <Kernel/Vector.hpp>

namespace Isaac {
  class Polygon {
  public:
    Polygon() noexcept;

    Polygon(const double &mass_, const std::vector<Vector> &vertices_, const Vector &position_, const Vector &velocity_,
            const Vector &acceleration_, const std::array<float, 4> &Color_) noexcept;

    Polygon(const Polygon &other) noexcept;

    [[nodiscard]] Vector getVertex(const int &index) const noexcept;

    [[nodiscard]] int getVertexCount() const noexcept;

    [[nodiscard]] double getMass() const;

    [[nodiscard]] Vector getPosition() const noexcept;

    void setPosition(const Vector &position_) noexcept;

    [[nodiscard]] Vector getVelocity() const noexcept;

    void setVelocity(const Vector &velocity_) noexcept;

    [[nodiscard]] Vector getAcceleration() const noexcept;

    void setAcceleration(const Vector &acceleration_) noexcept;

    [[nodiscard]] std::array<float, 4> getColor() const noexcept;

    static std::vector<Vector> breakVerticesIntoTriangles(const Vector &center_,
                                                          const std::vector<Vector> &vertices_) noexcept;

  private:
    double mass;
    std::vector<Vector> vertices;
    Vector position;
    Vector velocity;
    Vector acceleration;
    std::array<float, 4> Color;
  };
} // namespace Isaac

#endif // ISAAC_POLYGON_HPP
