#include "Kernel/Polygon.hpp"
#include "Kernel/RigidBody2D.hpp"
#include <gtest/gtest.h>
#include <random>

using Isaac::Kernel::Polygon;
using Isaac::Kernel::RigidBody2D;

class RigidBody2DTests : public ::testing::Test
{
protected:
    std::random_device rd;
    std::mt19937 x;

    void SetUp() override
    {
        std::random_device rd{};
        rd();
    }

    void TearDown() override
    {
    }
};

TEST_F(RigidBody2DTests, Constructor)
{
    std::normal_distribution f{-1E300, 1E300};
    std::normal_distribution M{1E-300, 1E300};
    std::uniform_int_distribution RNG{3, 100};

    // Random Polygons
    {
        for (int t = 1; t <= 1'00'000; ++t)
        {
            int vertexCount = RNG(x);

            std::vector<Vector2d> vertices(vertexCount);
            for (auto& vertex : vertices) { vertex = {f(x), f(x)}; }

            Vector2d s = {f(x), f(x)};
            Vector2d v = {f(x), f(x)};
            Vector2d a = {f(x), f(x)};

            Polygon polygon(vertexCount, vertices, s, v, a);

            double mass = M(x);

            RigidBody2D rigidPolygon(mass, polygon);

            RigidBody2D rigidPolygon_(rigidPolygon);
        }
    }
}

TEST_F(RigidBody2DTests, Getters)
{
    std::normal_distribution f{-1E300, 1E300};
    std::normal_distribution M{1E-300, 1E300};
    std::uniform_int_distribution RNG{3, 100};

    // Random Polygons
    {
        for (int t = 1; t <= 1'00'000; ++t)
        {
            int vertexCount = RNG(x);

            std::vector<Vector2d> vertices(vertexCount);
            for (auto& vertex : vertices) { vertex = {f(x), f(x)}; }

            Vector2d s = {f(x), f(x)};
            Vector2d v = {f(x), f(x)};
            Vector2d a = {f(x), f(x)};

            Polygon polygon(vertexCount, vertices, s, v, a);

            double mass = M(x);

            RigidBody2D rigidPolygon(mass, polygon);
            EXPECT_EQ(rigidPolygon.getVertexCount(), vertexCount);
            for (int i = 0; i < vertexCount; ++i)
            {
                EXPECT_EQ(rigidPolygon.getVertex(i), vertices[i]);
            }
            EXPECT_EQ(rigidPolygon.getMass(), mass);
            EXPECT_EQ(rigidPolygon.getPosition(), s);
            EXPECT_EQ(rigidPolygon.getVelocity(), v);
            EXPECT_EQ(rigidPolygon.getAcceleration(), a);
        }
    }
}

TEST_F(RigidBody2DTests, Setters)
{
    std::normal_distribution f{-1E300, 1E300};
    std::normal_distribution M{1E-300, 1E300};
    std::uniform_int_distribution RNG{3, 100};

    // Random Polygons
    {
        for (int t = 1; t <= 1'00'000; ++t)
        {
            int vertexCount = RNG(x);

            std::vector<Vector2d> vertices(vertexCount);
            for (auto& vertex : vertices) { vertex = {f(x), f(x)}; }

            Vector2d s = {f(x), f(x)};
            Vector2d v = {f(x), f(x)};
            Vector2d a = {f(x), f(x)};

            Polygon polygon(vertexCount, vertices, s, v, a);

            double mass = M(x);

            RigidBody2D rigidPolygon(mass, polygon);

            Vector2d s_ = {f(x), f(x)};
            Vector2d v_ = {f(x), f(x)};
            Vector2d a_ = {f(x), f(x)};

            std::vector<Vector2d> vertices_(vertexCount);
            for (auto& vertex : vertices_) { vertex = {f(x), f(x)}; }

            rigidPolygon.setPosition(s_);
            rigidPolygon.setVelocity(v_);
            rigidPolygon.setAcceleration(a_);
            rigidPolygon.setVertices(vertices_);

            EXPECT_EQ(rigidPolygon.getVertexCount(), vertexCount);
            for (int i = 0; i < vertexCount; ++i)
            {
                EXPECT_EQ(rigidPolygon.getVertex(i), vertices_[i]);
            }
            EXPECT_EQ(rigidPolygon.getMass(), mass);
            EXPECT_EQ(rigidPolygon.getPosition(), s_);
            EXPECT_EQ(rigidPolygon.getVelocity(), v_);
            EXPECT_EQ(rigidPolygon.getAcceleration(), a_);
        }
    }
}
