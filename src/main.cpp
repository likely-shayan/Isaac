#include <iostream>
#include <vector>
#include <memory>

#include <Eigen/Dense>

#include <Kernel/Polygon.hpp>
#include <Kernel/Mesh.hpp>
#include <Rendering/Window.hpp>

// Using declarations for Eigen
using Eigen::Vector3d;
using Eigen::Vector4d;

int main() {
    // Define the 36 vertices for a 1x1x1 cube centered at the origin.
    // A cube has 6 faces, and each face is 2 triangles, so 12 triangles total.
    // 12 triangles * 3 vertices/triangle = 36 vertices.
    std::vector<Vector3d> cubeVertices = {
        // Front face
        {-0.5, -0.5,  0.5}, { 0.5, -0.5,  0.5}, { 0.5,  0.5,  0.5},
        {-0.5, -0.5,  0.5}, { 0.5,  0.5,  0.5}, {-0.5,  0.5,  0.5},
        // Back face
        {-0.5, -0.5, -0.5}, { 0.5,  0.5, -0.5}, { 0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5}, {-0.5,  0.5, -0.5}, { 0.5,  0.5, -0.5},
        // Left face
        {-0.5, -0.5, -0.5}, {-0.5, -0.5,  0.5}, {-0.5,  0.5,  0.5},
        {-0.5, -0.5, -0.5}, {-0.5,  0.5,  0.5}, {-0.5,  0.5, -0.5},
        // Right face
        { 0.5, -0.5, -0.5}, { 0.5,  0.5,  0.5}, { 0.5, -0.5,  0.5},
        { 0.5, -0.5, -0.5}, { 0.5,  0.5, -0.5}, { 0.5,  0.5,  0.5},
        // Top face
        {-0.5,  0.5,  0.5}, { 0.5,  0.5,  0.5}, { 0.5,  0.5, -0.5},
        {-0.5,  0.5,  0.5}, { 0.5,  0.5, -0.5}, {-0.5,  0.5, -0.5},
        // Bottom face
        {-0.5, -0.5,  0.5}, { 0.5, -0.5, -0.5}, { 0.5, -0.5,  0.5},
        {-0.5, -0.5,  0.5}, {-0.5, -0.5, -0.5}, { 0.5, -0.5, -0.5}
    };

    // Create a vector to hold our scene objects (polygons)
    std::vector<std::shared_ptr<Isaac::Polygon>> polygons;

    // Create the first cube (red)
    auto cube1 = std::make_shared<Isaac::Polygon>(
        100000000000.0f,      // mass
        cubeVertices,         // vertices
        Vector3d{-2.0, 0.0, 0.0}, // initial position
        Vector3d{0.1, 0.0, 0.0},  // initial velocity
        Vector4d{1.0, 0.0, 0.0, 1.0} // color (red)
    );
    polygons.push_back(cube1);

    // Create the second cube (blue)
    auto cube2 = std::make_shared<Isaac::Polygon>(
        100000000000.0f,      // mass
        cubeVertices,         // vertices
        Vector3d{2.0, 0.5, 0.0},  // initial position
        Vector3d{-0.1, 0.0, 0.0}, // initial velocity
        Vector4d{0.0, 0.0, 1.0, 1.0} // color (blue)
    );
    polygons.push_back(cube2);

    // Create a mesh containing all our polygons
    auto mesh = std::make_unique<Isaac::Mesh>(polygons);

    // Create a window and pass the mesh to it
    Isaac::Window window(std::move(mesh));

    // Run the simulation
    window.Run();

    std::cout << "Isaac built successfully" << std::endl;

    return EXIT_SUCCESS;
}
