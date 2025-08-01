#include <iostream>
#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>

int main() {
  std::vector<std::unique_ptr<Isaac::Body> > bodies;

  Isaac::Tetrahedron tetrahedron(
    1,
    {{{0, 1000, 0}, {-1000, 0, 0}, {1000, 0, 0}, {0, 0, 1000}}},
    {2000, 0, 0},
    {0, 0, 0},
    {0, 0, 1, 1}
  );


  Isaac::Cube cube(
    1,
    1000,
    {-2000, 0, 0},
    {0, 0, 0},
    {0, 0, 1, 1}
  );


  Isaac::Octahedron octahedron(
    1,
    1000,
    {0, 0, -2000},
    {0, 0, 0},
    {0, 0, 1, 1}
  );

  Isaac::SquarePyramid square_pyramid(
    1,
    1000, 1000,
    {0, 0, 2000},
    {0, 0, 0},
    {0, 0, 1, 1}
  );

  Isaac::Dodecahedron dodecahedron(
    1,
    1000,
    {0, 2000, 0},
    {0, 0, 0},
    {0, 0, 1, 1}
  );

  Isaac::Icosahedron icosahedron(
    1,
    1000,
    {0, -2000, 0},
    {0, 0, 0},
    {0, 0, 1, 1}
  );

  Isaac::Sphere sphere(
    1,
    1000,
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 1, 1}
  );

  bodies.push_back(std::make_unique<Isaac::Tetrahedron>(std::move(tetrahedron)));
  bodies.push_back(std::make_unique<Isaac::Cube>(std::move(cube)));
  bodies.push_back(std::make_unique<Isaac::Octahedron>(std::move(octahedron)));
  bodies.push_back(std::make_unique<Isaac::SquarePyramid>(std::move(square_pyramid)));
  bodies.push_back(std::make_unique<Isaac::Dodecahedron>(std::move(dodecahedron)));
  bodies.push_back(std::make_unique<Isaac::Icosahedron>(std::move(icosahedron)));
  bodies.push_back(std::make_unique<Isaac::Sphere>(std::move(sphere)));

  Isaac::Mesh mesh(std::move(bodies));

  Isaac::Window window(mesh);

  window.Run();

  return EXIT_SUCCESS;
}
