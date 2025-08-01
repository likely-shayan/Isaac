// A massive high-speed particle passes through a cluster of lightweight stationary particles

#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>
#include <random>

int main() {
  std::vector<std::unique_ptr<Isaac::Body> > particles;

  constexpr int clusterSize = 100;
  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<double> dist(-500, 500);
  for (int i = 0; i < clusterSize; ++i) {
    particles.emplace_back(std::make_unique<Isaac::Sphere>(Isaac::Sphere(
        10.0,
        50,
        {dist(rng), dist(rng), dist(rng)},
        {0, 0, 0},
        {0.5, 0.5, 1, 1}
      )
    ));
  }

  particles.emplace_back(std::make_unique<Isaac::Sphere>(Isaac::Sphere(
      1E+20,
      60,
      {5000, 5000, 5000},
      {-10000, -10000, -10000},
      {1, 1, 1, 1}
    )
  ));

  Isaac::Mesh mesh(std::move(particles));
  Isaac::Window window(mesh);
  window.Run();

  return EXIT_SUCCESS;
}
