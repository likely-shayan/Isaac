// Transfer of Kinetic Energy as Moving Sphere Collides With Stationary Sphere

#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>

using Eigen::Vector3d;

int main() {
  constexpr int Bodies = 50;
  std::vector<std::unique_ptr<Isaac::Body> > polygons(Bodies);

  for (int i = 1; i < Bodies; ++i) {
    polygons[i] = std::make_unique<Isaac::Sphere>(Isaac::Sphere(
      1E+1,
      10,
      {100.0 * i, 0, 9500},
      {-100, 0, 0},
      {1, 0, 0, 1}
    ));
  }

  polygons[0] = std::make_unique<Isaac::Sphere>(Isaac::Sphere(1E+1, 10, {0, 0, 9500}, {0, 0, 0}, {1, 0, 0, 1}));

  Isaac::Mesh mesh(std::move(polygons));

  Isaac::Window window(mesh);

  window.Run();

  return EXIT_SUCCESS;
}
