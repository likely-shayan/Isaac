#ifndef ISAAC_CUBE_HPP
#define ISAAC_CUBE_HPP

#include <Kernel/Body.hpp>

namespace Isaac {
  class Cube final : public Body {
  public:
    Cube() noexcept;

    Cube(const double &mass_, const double &length_, const Vector3d &position_, const Vector3d &velocity_,
         const Vector4d &color_) noexcept;

    Cube(const Cube &other) noexcept;

  private:
    static std::vector<Vector3d> constructCubeVertices(const double &length_) noexcept;
  };
} // namespace Isaac

#endif // ISAAC_CUBE_HPP
