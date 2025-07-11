#ifndef ISAAC_POLYGON_HPP
#define ISAAC_POLYGON_HPP

#include <vector>
#include <Kernel/Vector.hpp>

namespace Isaac {
  class Polygon {
  public:
    Polygon() noexcept;

    Polygon(const double &mass_, const std::vector<Vector> &vertices_, const Vector &position_, const Vector &velocity_,
            const std::vector<float> &Color_) noexcept;

    Polygon(const Polygon &other) noexcept;

    [[nodiscard]] Vector getVertex(const std::size_t &index) const noexcept;

    [[nodiscard]] std::size_t getVertexCount() const noexcept;

    [[nodiscard]] double getMass() const;

    [[nodiscard]] Vector getPosition() const noexcept;

    void setPosition(const Vector &position_) noexcept;

    [[nodiscard]] Vector getVelocity() const noexcept;

    void setVelocity(const Vector &velocity_) noexcept;

    [[nodiscard]] Vector getAcceleration() const noexcept;

    void setAcceleration(const Vector &acceleration_) noexcept;

    [[nodiscard]] std::vector<float> getColor() const noexcept;

    static std::vector<Vector> breakVerticesIntoTriangles(const std::vector<Vector> &vertices_) noexcept;

    static std::vector<Vector> constructCircleVertices(const double &radius,
                                                       const std::size_t &totalVertices = 360) noexcept;

  private:
    double mass;
    std::vector<Vector> vertices;
    Vector position;
    Vector velocity;
    Vector acceleration;
    std::vector<float> Color;
  };
} // namespace Isaac

#endif // ISAAC_POLYGON_HPP
