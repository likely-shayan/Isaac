// A massive high-speed particle passes through a cluster of lightweight stationary particles

#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>
#include <random>

std::vector<Vector3d> createSphereVertices(const double radius, const int stackCount = 12, const int sectorCount = 24) {
    std::vector<Vector3d> vertices;
    for (int i = 0; i < stackCount; ++i) {
        const double stackAngle1 = M_PI / 2.0 - static_cast<double>(i) * M_PI / static_cast<double>(stackCount);
        const double stackAngle2 = M_PI / 2.0 - static_cast<double>(i + 1) * M_PI / static_cast<double>(stackCount);
        for (int j = 0; j < sectorCount; ++j) {
            const double sectorAngle1 = static_cast<double>(j) * 2.0 * M_PI / static_cast<double>(sectorCount);
            const double sectorAngle2 = static_cast<double>(j + 1) * 2.0 * M_PI / static_cast<double>(sectorCount);
            Vector3d v1(radius * std::cos(stackAngle1) * std::cos(sectorAngle1), radius * std::cos(stackAngle1) * std::sin(sectorAngle1), radius * std::sin(stackAngle1));
            Vector3d v2(radius * std::cos(stackAngle1) * std::cos(sectorAngle2), radius * std::cos(stackAngle1) * std::sin(sectorAngle2), radius * std::sin(stackAngle1));
            Vector3d v3(radius * std::cos(stackAngle2) * std::cos(sectorAngle2), radius * std::cos(stackAngle2) * std::sin(sectorAngle2), radius * std::sin(stackAngle2));
            Vector3d v4(radius * std::cos(stackAngle2) * std::cos(sectorAngle1), radius * std::cos(stackAngle2) * std::sin(sectorAngle1), radius * std::sin(stackAngle2));
            vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v4);
            vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
        }
    }
    return vertices;
}

int main() {
    std::vector<Isaac::Polygon> particles;
    const auto particleVertices = createSphereVertices(50.0);

    constexpr int clusterSize = 100;
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(-500, 500);
    for (int i = 0; i < clusterSize; ++i) {
        particles.emplace_back(Isaac::Polygon(
            10.0,
            particleVertices,
            {dist(rng), dist(rng), dist(rng)},
            {0, 0, 0},
            {0.5, 0.5, 1, 1}
            )
        );
    }

    particles.emplace_back(Isaac::Polygon(
        1E+20,
        createSphereVertices(60.0),
        {5000, 5000, 5000},
        {-10000, -10000, -10000},
        {1, 1, 1, 1}
        )
    );

    Isaac::Mesh mesh(particles);
    Isaac::Window window(std::make_shared<Isaac::Mesh>(mesh));
    window.Run();

    return EXIT_SUCCESS;
}