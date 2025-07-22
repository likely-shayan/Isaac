// A red sphere of radius 1000 centered at origin

#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>

int main() {
  std::vector<Vector3d> sphereVertices;

  constexpr int stackCount = 18;
  for (int i = 0; i < stackCount; ++i) {
    constexpr int sectorCount = 36;
    const double stackAngle1 = M_PI / 2.0 - static_cast<double>(i) * M_PI / static_cast<double>(stackCount);
    const double stackAngle2 = M_PI / 2.0 - static_cast<double>(i + 1) * M_PI / static_cast<double>(stackCount);

    for (int j = 0; j < sectorCount; ++j) {
      constexpr double radius = 1000.0;
      const double sectorAngle1 = static_cast<double>(j) * 2.0 * M_PI / static_cast<double>(sectorCount);
      const double sectorAngle2 = static_cast<double>(j + 1) * 2.0 * M_PI / static_cast<double>(sectorCount);

      Vector3d v1(
        radius * std::cos(stackAngle1) * std::cos(sectorAngle1),
        radius * std::cos(stackAngle1) * std::sin(sectorAngle1),
        radius * std::sin(stackAngle1)
      );
      Vector3d v2(
        radius * std::cos(stackAngle1) * std::cos(sectorAngle2),
        radius * std::cos(stackAngle1) * std::sin(sectorAngle2),
        radius * std::sin(stackAngle1)
      );
      Vector3d v3(
        radius * std::cos(stackAngle2) * std::cos(sectorAngle2),
        radius * std::cos(stackAngle2) * std::sin(sectorAngle2),
        radius * std::sin(stackAngle2)
      );
      Vector3d v4(
        radius * std::cos(stackAngle2) * std::cos(sectorAngle1),
        radius * std::cos(stackAngle2) * std::sin(sectorAngle1),
        radius * std::sin(stackAngle2)
      );

      sphereVertices.push_back(v1);
      sphereVertices.push_back(v2);
      sphereVertices.push_back(v4);

      sphereVertices.push_back(v2);
      sphereVertices.push_back(v3);
      sphereVertices.push_back(v4);
    }
  }

  Isaac::Polygon sphere(
    1,
    sphereVertices,
    {0, 0, 0},
    {0, 0, 0},
    {1, 0, 0, 1}
  );

  Isaac::Mesh mesh(
    {std::make_shared<Isaac::Polygon>(sphere)}
  );

  Isaac::Window window(
    std::make_shared<Isaac::Mesh>(mesh)
  );

  window.Run();

  return EXIT_SUCCESS;
}
