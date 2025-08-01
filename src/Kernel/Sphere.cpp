#include <Kernel/Sphere.hpp>

namespace Isaac {
  Sphere::Sphere() noexcept = default;

  Sphere::Sphere(const double &mass_, const double &radius_, const Vector3d &position_, const Vector3d &velocity_,
                 const Vector4d &color_) noexcept : Body(mass_, constructSphereVertices(radius_), position_, velocity_,
                                                         color_) {
  }

  Sphere::Sphere(const Sphere &other) noexcept = default;

  std::vector<Vector3d> Sphere::constructSphereVertices(const double &radius_) noexcept {
    std::vector<Vector3d> vertices;
    constexpr int stackCount = 18;
    for (int i = 0; i < stackCount; ++i) {
      constexpr int sectorCount = 36;
      const double stackAngle1 = M_PI / 2.0 - static_cast<double>(i) * M_PI / static_cast<double>(stackCount);
      const double stackAngle2 = M_PI / 2.0 - static_cast<double>(i + 1) * M_PI / static_cast<double>(stackCount);

      for (int j = 0; j < sectorCount; ++j) {
        const double sectorAngle1 = static_cast<double>(j) * 2.0 * M_PI / static_cast<double>(sectorCount);
        const double sectorAngle2 = static_cast<double>(j + 1) * 2.0 * M_PI / static_cast<double>(sectorCount);

        Vector3d v1(
          radius_ * std::cos(stackAngle1) * std::cos(sectorAngle1),
          radius_ * std::cos(stackAngle1) * std::sin(sectorAngle1),
          radius_ * std::sin(stackAngle1)
        );
        Vector3d v2(
          radius_ * std::cos(stackAngle1) * std::cos(sectorAngle2),
          radius_ * std::cos(stackAngle1) * std::sin(sectorAngle2),
          radius_ * std::sin(stackAngle1)
        );
        Vector3d v3(
          radius_ * std::cos(stackAngle2) * std::cos(sectorAngle2),
          radius_ * std::cos(stackAngle2) * std::sin(sectorAngle2),
          radius_ * std::sin(stackAngle2)
        );
        Vector3d v4(
          radius_ * std::cos(stackAngle2) * std::cos(sectorAngle1),
          radius_ * std::cos(stackAngle2) * std::sin(sectorAngle1),
          radius_ * std::sin(stackAngle2)
        );

        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v4);

        vertices.push_back(v2);
        vertices.push_back(v3);
        vertices.push_back(v4);
      }
    }
    return vertices;
  }
} // namespace Isaac
