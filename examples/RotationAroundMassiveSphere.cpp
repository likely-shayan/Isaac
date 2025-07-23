// Rotation of a blue sphere around a massive (1E+19) moving red sphere

#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>

int main() {
  std::vector<Vector3d> massiveSphereVertices, smallSphereVertices;

  constexpr int stackCount = 18;
  for (int i = 0; i < stackCount; ++i) {
    constexpr int sectorCount = 36;
    const double stackAngle1 = M_PI / 2.0 - static_cast<double>(i) * M_PI / static_cast<double>(stackCount);
    const double stackAngle2 = M_PI / 2.0 - static_cast<double>(i + 1) * M_PI / static_cast<double>(stackCount);

    for (int j = 0; j < sectorCount; ++j) {
      constexpr double massiveRadius = 100.0;
      constexpr double smallRadius = 30.0;
      const double sectorAngle1 = static_cast<double>(j) * 2.0 * M_PI / static_cast<double>(sectorCount);
      const double sectorAngle2 = static_cast<double>(j + 1) * 2.0 * M_PI / static_cast<double>(sectorCount);

      Vector3d v1(
        massiveRadius * std::cos(stackAngle1) * std::cos(sectorAngle1),
        massiveRadius * std::cos(stackAngle1) * std::sin(sectorAngle1),
        massiveRadius * std::sin(stackAngle1)
      );
      Vector3d v2(
        massiveRadius * std::cos(stackAngle1) * std::cos(sectorAngle2),
        massiveRadius * std::cos(stackAngle1) * std::sin(sectorAngle2),
        massiveRadius * std::sin(stackAngle1)
      );
      Vector3d v3(
        massiveRadius * std::cos(stackAngle2) * std::cos(sectorAngle2),
        massiveRadius * std::cos(stackAngle2) * std::sin(sectorAngle2),
        massiveRadius * std::sin(stackAngle2)
      );
      Vector3d v4(
        massiveRadius * std::cos(stackAngle2) * std::cos(sectorAngle1),
        massiveRadius * std::cos(stackAngle2) * std::sin(sectorAngle1),
        massiveRadius * std::sin(stackAngle2)
      );

      Vector3d v1_(
        smallRadius * std::cos(stackAngle1) * std::cos(sectorAngle1),
        smallRadius * std::cos(stackAngle1) * std::sin(sectorAngle1),
        smallRadius * std::sin(stackAngle1)
      );
      Vector3d v2_(
        smallRadius * std::cos(stackAngle1) * std::cos(sectorAngle2),
        smallRadius * std::cos(stackAngle1) * std::sin(sectorAngle2),
        smallRadius * std::sin(stackAngle1)
      );
      Vector3d v3_(
        smallRadius * std::cos(stackAngle2) * std::cos(sectorAngle2),
        smallRadius * std::cos(stackAngle2) * std::sin(sectorAngle2),
        smallRadius * std::sin(stackAngle2)
      );
      Vector3d v4_(
        smallRadius * std::cos(stackAngle2) * std::cos(sectorAngle1),
        smallRadius * std::cos(stackAngle2) * std::sin(sectorAngle1),
        smallRadius * std::sin(stackAngle2)
      );

      massiveSphereVertices.push_back(v1);
      massiveSphereVertices.push_back(v2);
      massiveSphereVertices.push_back(v4);

      massiveSphereVertices.push_back(v2);
      massiveSphereVertices.push_back(v3);
      massiveSphereVertices.push_back(v4);

      smallSphereVertices.push_back(v1_);
      smallSphereVertices.push_back(v2_);
      smallSphereVertices.push_back(v4_);

      smallSphereVertices.push_back(v2_);
      smallSphereVertices.push_back(v3_);
      smallSphereVertices.push_back(v4_);
    }
  }

  Isaac::Polygon massiveSphere(
    1E+19,
    massiveSphereVertices,
    {0, 0, 5000},
    {500, 0, 0},
    {1, 0, 0, 1}
  );

  Isaac::Polygon smallSphere(
    1,
    smallSphereVertices,
    {0, 1500, 5000},
    {0, 0, 0},
    {0, 0, 1, 1}
  );

  Isaac::Mesh mesh(
    {massiveSphere, smallSphere}
  );

  Isaac::Window window(
    std::make_shared<Isaac::Mesh>(mesh)
  );

  window.Run();

  return EXIT_SUCCESS;
}
