// A chain reaction of collisions, started by one moving sphere.

#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>

std::vector<Vector3d> createSphereVertices(const double radius, const int stackCount = 18, const int sectorCount = 36) {
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
    constexpr int numSpheres = 8;
    constexpr double radius = 100.0;
    std::vector<Isaac::Polygon> spheres;
    const auto sphereVertices = createSphereVertices(radius);

    for (int i = 0; i < numSpheres - 1; ++i) {
        spheres.emplace_back(Isaac::Polygon(
            10.0,
            sphereVertices,
            {(i * 2.0 * radius) + 1500, 0, 5000},
            {0, 0, 0},
            {1, 0, 0, 1}
            )
        );
    }

    spheres.emplace_back(Isaac::Polygon(
        10.0,
        sphereVertices,
        {-500, 0, 5000},
        {1000, 0, 0},
        {1, 1, 1, 1}
        )
    );

    Isaac::Mesh mesh(spheres);
    Isaac::Window window(std::make_shared<Isaac::Mesh>(mesh));
    window.Run();

    return EXIT_SUCCESS;
}