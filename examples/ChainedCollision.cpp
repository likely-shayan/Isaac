// A chain reaction of collisions, started by one moving sphere.

#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>

int main() {
  constexpr int numSpheres = 8;
  constexpr double radius = 100.0;
  std::vector<std::unique_ptr<Isaac::Body> > spheres;

  for (int i = 0; i < numSpheres - 1; ++i) {
    spheres.push_back(std::make_unique<Isaac::Sphere>(Isaac::Sphere(
        10.0,
        radius,
        {(i * 2.0 * radius) + 1500, 0, 5000},
        {0, 0, 0},
        {1, 0, 0, 1}
      )
    ));
  }

  spheres.push_back(std::make_unique<Isaac::Sphere>(Isaac::Sphere(
      10.0,
      radius,
      {-500, 0, 5000},
      {1000, 0, 0},
      {1, 1, 1, 1}
    )
  ));

  Isaac::Mesh mesh(std::move(spheres));
  Isaac::Window window(mesh);
  window.Run();

  return EXIT_SUCCESS;
}
