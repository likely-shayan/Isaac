#include "Kernel/Polygon.hpp"
#include <gtest/gtest.h>
#include <random>
#include <vector>

using Isaac::Kernel::Polygon;

class PolygonTests : public ::testing::Test {
protected:
  std::random_device rd;
  std::mt19937 x;

  void SetUp() override {
    std::random_device rd{};
    std::mt19937 x{rd()};
  }

  void TearDown() override {}
};

TEST_F(PolygonTests, Constructor) {
  std::normal_distribution f{-1E300, 1E300};
  std::uniform_int_distribution RNG{3, 100};

  for (int t = 1; t <= 1'000; ++t) {
    int vertexCount = RNG(x);

    std::vector<Vector2d> vertices(vertexCount);
    for (auto &vertex : vertices) { vertex = {f(x), f(x)}; }

    Vector2d s = {f(x), f(x)};
    Vector2d v = {f(x), f(x)};
    Vector2d a = {f(x), f(x)};

    Polygon polygon(vertexCount, vertices, s, v, a);

    Polygon polygon_(polygon);
  }
}

TEST_F(PolygonTests, Getters) {
  std::normal_distribution f{-1E300, 1E300};
  std::uniform_int_distribution RNG{3, 100};

  for (int t = 1; t <= 1'000; ++t) {
    int vertexCount = RNG(x);

    std::vector<Vector2d> vertices(vertexCount);
    for (auto &vertex : vertices) { vertex = {f(x), f(x)}; }

    Vector2d s = {f(x), f(x)};
    Vector2d v = {f(x), f(x)};
    Vector2d a = {f(x), f(x)};

    Polygon polygon(vertexCount, vertices, s, v, a);

    EXPECT_EQ(polygon.getVertexCount(), vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
      EXPECT_EQ(polygon.getVertex(i), vertices[i]);
    }
  }
}

TEST_F(PolygonTests, Setters) {
  std::normal_distribution f{-1E300, 1E300};
  std::uniform_int_distribution RNG{3, 100};

  for (int t = 1; t <= 1'000; ++t) {
    int vertexCount = RNG(x);

    std::vector<Vector2d> vertices(vertexCount);
    for (auto &vertex : vertices) { vertex = {f(x), f(x)}; }

    Vector2d s = {f(x), f(x)};
    Vector2d v = {f(x), f(x)};
    Vector2d a = {f(x), f(x)};

    Polygon polygon(vertexCount, vertices, s, v, a);

    for (int i = 0; i < vertexCount; ++i) {
      Vector2d newVertex = {f(x), f(x)};
      polygon.setVertex(i, newVertex);
      EXPECT_EQ(polygon.getVertex(i), newVertex);
    }

    std::vector<Vector2d> newVertices(vertexCount);
    for (auto &vertex : newVertices) { vertex = {f(x), f(x)}; }

    polygon.setVertices(newVertices);

    for (int i = 0; i < vertexCount; ++i) {
      EXPECT_EQ(polygon.getVertex(i), newVertices[i]);
    }
  }
}
