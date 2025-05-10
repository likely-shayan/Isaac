#include <gtest/gtest.h>
#include "Kernel/Polygon.hpp"
#include "Kernel/RigidBody2D.hpp"
#include "Rendering/Renderable_Object_2D.hpp"
#include <random>
#include <vector>

using Isaac::Kernel::Polygon;
using Isaac::Kernel::RigidBody2D;
using Isaac::Rendering::Renderable_Object_2D;


class Renderable_Object_2D_Tests : public ::testing::Test
{
protected:
    std::random_device rd;
    std::mt19937 x;

    void SetUp() override
    {
        std::random_device rd;
        rd();
    }

    void TearDown() override
    {
    }
};

TEST_F(Renderable_Object_2D_Tests, Constructor)
{
    std::normal_distribution f{-1E38, 1E38};
    std::normal_distribution M{1E-300, 1E38};
    std::normal_distribution<float> C{1E-1, 1E0};
    std::uniform_int_distribution RNG{3, 100};
    std::uniform_int_distribution S{1, 10'000};

    // Random Polygons
    {
        for (int t = 1; t <= 10'000; ++t)
        {
            int vertexCount = RNG(x);

            std::vector<Vector2f> vertices(vertexCount);
            for (auto& vertex : vertices) { vertex = {f(x), f(x)}; }

            Vector2f s = {f(x), f(x)};
            Vector2f v = {f(x), f(x)};
            Vector2f a = {f(x), f(x)};

            Polygon polygon(vertexCount, vertices, s, v, a);

            double mass = M(x);

            RigidBody2D rigidPolygon(mass, polygon);

            std::vector<float> Color = {C(x), C(x), C(x), C(x)};
            int screenWidth = S(x);
            int screenHeight = S(x);

            Renderable_Object_2D renderableObject(rigidPolygon, Color, screenWidth, screenHeight);
        }
    }
}

std::vector<float> decompose_2D_Coordinates(const int& screenWidth_, const int& screenHeight_,
                                            const Vector2f& vector_) noexcept;

TEST_F(Renderable_Object_2D_Tests, Getters)
{
    std::normal_distribution f{-1E38, 1E38};
    std::normal_distribution M{1E-300, 1E38};
    std::normal_distribution<float> C{1E-1, 1E0};
    std::uniform_int_distribution RNG{3, 100};
    std::uniform_int_distribution S{1, 10'000};

    // Random Polygons
    {
        for (int t = 1; t <= 10'000; ++t)
        {
            int vertexCount = RNG(x);

            std::vector<Vector2f> vertices(vertexCount);
            for (auto& vertex : vertices) { vertex = {f(x), f(x)}; }

            Vector2f s = {f(x), f(x)};
            Vector2f v = {f(x), f(x)};
            Vector2f a = {f(x), f(x)};

            Polygon polygon(vertexCount, vertices, s, v, a);

            double mass = M(x);

            RigidBody2D rigidPolygon(mass, polygon);

            std::vector Color = {C(x), C(x), C(x), C(x)};
            int screenWidth = S(x);
            int screenHeight = S(x);

            Renderable_Object_2D renderableObject(rigidPolygon, Color, screenWidth, screenHeight);

            std::vector<float> Coordinates = renderableObject.getCoordinates();
            EXPECT_EQ(Coordinates.size(), 3 * vertexCount);
            for (int i = 0; i < 3 * vertexCount; i += 3)
            {
                std::vector<float> V = decompose_2D_Coordinates(screenWidth, screenHeight, s + vertices[i / 3]);
                EXPECT_EQ(Coordinates[i], V[0]);
                EXPECT_EQ(Coordinates[i+1], V[1]);
                EXPECT_EQ(Coordinates[i+2], V[2]);
            }

            std::vector<int> Indices = renderableObject.getIndices();
            EXPECT_EQ(Indices.size(), 3 * (vertexCount - 2));
            int x = 1;
            for (int i = 0; i < 3 * (vertexCount - 2); i += 3)
            {
                Indices[i] = 0;
                Indices[i + 1] = x;
                Indices[i + 2] = x + 1;
                x++;
            }

            std::vector<float> Colour = renderableObject.getColor();
            for (int i = 0; i < 4; i++)
            {
                EXPECT_EQ(Color[i], Colour[i]);
            }
        }
    }
}

std::vector<float> decompose_2D_Coordinates(const int& screenWidth_, const int& screenHeight_,
                                            const Vector2f& vector_) noexcept
{
    const float aspectRatio = std::max(screenHeight_, screenWidth_) / std::min(screenHeight_, screenWidth_);

    if (screenWidth_ > screenHeight_)
    {
        return {vector_.x() / screenWidth_, aspectRatio * vector_.y() / screenHeight_, 0.0};
    }
    if (screenHeight_ > screenWidth_)
    {
        return {aspectRatio * vector_.x() / screenWidth_, vector_.y() / screenHeight_, 0.0};
    }

    return {vector_.x() / screenWidth_, vector_.y() / screenHeight_, 0.0};
}
