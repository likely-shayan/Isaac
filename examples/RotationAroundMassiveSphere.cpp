// Rotation of a blue sphere around a massive (1E+19) moving red sphere

#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>

int main() {
  std::vector<std::unique_ptr<Isaac::Body> > spheres;

  Isaac::Sphere massiveSphere(
    1E+19,
    100,
    {0, 0, 5000},
    {500, 0, 0},
    {1, 0, 0, 1}
  );

  Isaac::Sphere smallSphere(
    1,
    30,
    {0, 1500, 5000},
    {0, 0, 0},
    {0, 0, 1, 1}
  );

  spheres.push_back(std::make_unique<Isaac::Sphere>(std::move(massiveSphere)));
  spheres.push_back(std::make_unique<Isaac::Sphere>(std::move(smallSphere)));


  Isaac::Mesh mesh(
    std::move(spheres)
  );

  Isaac::Window window(
    mesh
  );

  window.Run();

  return EXIT_SUCCESS;
}
