// Two massive bodies of equal mass orbiting each other.

#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>

int main() {
  std::vector<std::unique_ptr<Isaac::Body> > bodies;

  Isaac::Sphere body1(
    2E+20,
    100,
    {-2000, 0, 0},
    {0, -1000, 0},
    {1, 0.5, 0, 1}
  );

  Isaac::Sphere body2(
    2E+20,
    100,
    {2000, 0, 0},
    {0, 1000, 0},
    {0.5, 0.8, 1, 1}
  );

  bodies.push_back(std::make_unique<Isaac::Sphere>(std::move(body1)));
  bodies.push_back(std::make_unique<Isaac::Sphere>(std::move(body2)));

  Isaac::Mesh mesh(std::move(bodies));
  Isaac::Window window(mesh);
  window.Run();

  return EXIT_SUCCESS;
}
