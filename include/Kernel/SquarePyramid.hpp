#ifndef ISAAC_SQUAREPYRAMID_HPP
#define ISAAC_SQUAREPYRAMID_HPP

#include <Kernel/Body.hpp>

namespace Isaac {
  class SquarePyramid final : public Body {
  public:
    SquarePyramid() noexcept;

    SquarePyramid(const double &mass_, const double &sideLength_, const double &height_, const Vector3d &position_,
                  const Vector3d &velocity_, const Vector4d &color_) noexcept;

    SquarePyramid(const SquarePyramid &other) noexcept;

  private:
    static std::vector<Vector3d> constructSquarePyramidVertices(const double &sideLength_,
                                                                const double &height_) noexcept;
  };
} // namespace Isaac

#endif // ISAAC_SQUAREPYRAMID_HPP
