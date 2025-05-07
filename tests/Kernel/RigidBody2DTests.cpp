#include "Kernel/Circle.hpp"
#include "Kernel/Curve2D.hpp"
#include "Kernel/Polygon.hpp"
#include "Kernel/RigidBody2D.hpp"
#include <gtest/gtest.h>
#include <random>

using Isaac::Kernel::Circle;
using Isaac::Kernel::Curve2D;
using Isaac::Kernel::CurveType2D;
using Isaac::Kernel::Polygon;
using Isaac::Kernel::RigidBody2D;

class RigidBody2DTests : public ::testing::Test {
protected:
  std::random_device rd;
  std::mt19937 x;

  void SetUp() override {
    std::random_device rd{};
    std::mt19937 x{rd()};
  }

  void TearDown() override {}
};

TEST_F(RigidBody2DTests, Constructor) {
  std::normal_distribution f{-1E300, 1E300};
  std::normal_distribution M{1E-300, 1E300};
  std::normal_distribution R{1E-300, 1E300};
  std::uniform_int_distribution RNG{3, 100};

  // No specified CurveType2D
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Curve2D curveCircle(CurveType2D::CircleType, s, v, a);
      Curve2D curvePolygon(CurveType2D::PolygonType, s, v, a);

      double mass = M(x);

      RigidBody2D rigidCircle(mass, curveCircle);
      RigidBody2D rigidPolygon(mass, curvePolygon);

      RigidBody2D rigidCircle_(rigidCircle);
      RigidBody2D rigidPolygon_(rigidPolygon);
    }
  }

  // CurveType2D::CircleType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      double r = R(x);
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Circle circle(r, s, v, a);

      double mass = M(x);

      RigidBody2D rigidCircle(mass, circle);

      RigidBody2D rigidCircle_(rigidCircle);
    }
  }

  // CurveType2D::PolygonType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      int vertexCount = RNG(x);

      std::vector<Vector2d> vertices(vertexCount);
      for (auto &vertex : vertices) { vertex = {f(x), f(x)}; }

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

TEST_F(RigidBody2DTests, Getters) {
  std::normal_distribution f{-1E300, 1E300};
  std::normal_distribution M{1E-300, 1E300};
  std::normal_distribution R{1E-300, 1E300};
  std::uniform_int_distribution RNG{3, 100};

  // No specified CurveType2D
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Curve2D curveCircle(CurveType2D::CircleType, s, v, a);
      Curve2D curvePolygon(CurveType2D::PolygonType, s, v, a);

      double mass = M(x);

      RigidBody2D rigidCircle(mass, curveCircle);
      EXPECT_EQ(rigidCircle.getCurveType(), CurveType2D::CircleType);
      EXPECT_EQ(rigidCircle.getMass(), mass);
      EXPECT_EQ(rigidCircle.getPosition(), s);
      EXPECT_EQ(rigidCircle.getVelocity(), v);
      EXPECT_EQ(rigidCircle.getAcceleration(), a);

      RigidBody2D rigidPolygon(mass, curvePolygon);
      EXPECT_EQ(rigidPolygon.getCurveType(), CurveType2D::PolygonType);
      EXPECT_EQ(rigidPolygon.getMass(), mass);
      EXPECT_EQ(rigidPolygon.getPosition(), s);
      EXPECT_EQ(rigidPolygon.getVelocity(), v);
      EXPECT_EQ(rigidPolygon.getAcceleration(), a);
    }
  }

  // CurveType2D::CircleType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      double r = R(x);
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Circle circle(r, s, v, a);

      double mass = M(x);

      RigidBody2D rigidCircle(mass, circle);
      EXPECT_EQ(rigidCircle.getCurveType(), CurveType2D::CircleType);
      EXPECT_EQ(rigidCircle.getRadius(), r);
      EXPECT_EQ(rigidCircle.getMass(), mass);
      EXPECT_EQ(rigidCircle.getPosition(), s);
      EXPECT_EQ(rigidCircle.getVelocity(), v);
      EXPECT_EQ(rigidCircle.getAcceleration(), a);
    }
  }

  // CurveType2D::PolygonType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      int vertexCount = RNG(x);

      std::vector<Vector2d> vertices(vertexCount);
      for (auto &vertex : vertices) { vertex = {f(x), f(x)}; }

      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Polygon polygon(vertexCount, vertices, s, v, a);

      double mass = M(x);

      RigidBody2D rigidPolygon(mass, polygon);
      EXPECT_EQ(rigidPolygon.getCurveType(), CurveType2D::PolygonType);
      EXPECT_EQ(rigidPolygon.getVertexCount(), vertexCount);
      for (int i = 0; i < vertexCount; ++i) {
        EXPECT_EQ(rigidPolygon.getVertex(i), vertices[i]);
      }
      EXPECT_EQ(rigidPolygon.getMass(), mass);
      EXPECT_EQ(rigidPolygon.getPosition(), s);
      EXPECT_EQ(rigidPolygon.getVelocity(), v);
      EXPECT_EQ(rigidPolygon.getAcceleration(), a);
    }
  }
}

TEST_F(RigidBody2DTests, Setters) {
  std::normal_distribution f{-1E300, 1E300};
  std::normal_distribution M{1E-300, 1E300};
  std::normal_distribution R{1E-300, 1E300};
  std::uniform_int_distribution RNG{3, 100};

  // No specified CurveType2D
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Curve2D curveCircle(CurveType2D::CircleType, s, v, a);
      Curve2D curvePolygon(CurveType2D::PolygonType, s, v, a);

      double mass = M(x);

      Vector2d s_ = {f(x), f(x)};
      Vector2d v_ = {f(x), f(x)};
      Vector2d a_ = {f(x), f(x)};

      RigidBody2D rigidCircle(mass, curveCircle);

      rigidCircle.setPosition(s_);
      rigidCircle.setVelocity(v_);
      rigidCircle.setAcceleration(a_);

      EXPECT_EQ(rigidCircle.getCurveType(), CurveType2D::CircleType);
      EXPECT_EQ(rigidCircle.getMass(), mass);
      EXPECT_EQ(rigidCircle.getPosition(), s_);
      EXPECT_EQ(rigidCircle.getVelocity(), v_);
      EXPECT_EQ(rigidCircle.getAcceleration(), a_);

      RigidBody2D rigidPolygon(mass, curvePolygon);

      rigidPolygon.setPosition(s_);
      rigidPolygon.setVelocity(v_);
      rigidPolygon.setAcceleration(a_);

      EXPECT_EQ(rigidPolygon.getCurveType(), CurveType2D::PolygonType);
      EXPECT_EQ(rigidPolygon.getMass(), mass);
      EXPECT_EQ(rigidPolygon.getPosition(), s_);
      EXPECT_EQ(rigidPolygon.getVelocity(), v_);
      EXPECT_EQ(rigidPolygon.getAcceleration(), a_);
    }
  }

  // CurveType2D::CircleType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      double r = R(x);
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Circle circle(r, s, v, a);

      double mass = M(x);

      RigidBody2D rigidCircle(mass, circle);

      Vector2d s_ = {f(x), f(x)};
      Vector2d v_ = {f(x), f(x)};
      Vector2d a_ = {f(x), f(x)};

      rigidCircle.setPosition(s_);
      rigidCircle.setVelocity(v_);
      rigidCircle.setAcceleration(a_);

      EXPECT_EQ(rigidCircle.getCurveType(), CurveType2D::CircleType);
      EXPECT_EQ(rigidCircle.getRadius(), r);
      EXPECT_EQ(rigidCircle.getMass(), mass);
      EXPECT_EQ(rigidCircle.getPosition(), s_);
      EXPECT_EQ(rigidCircle.getVelocity(), v_);
      EXPECT_EQ(rigidCircle.getAcceleration(), a_);
    }
  }

  // CurveType2D::PolygonType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      int vertexCount = RNG(x);

      std::vector<Vector2d> vertices(vertexCount);
      for (auto &vertex : vertices) { vertex = {f(x), f(x)}; }

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
      for (auto &vertex : vertices_) { vertex = {f(x), f(x)}; }

      rigidPolygon.setPosition(s_);
      rigidPolygon.setVelocity(v_);
      rigidPolygon.setAcceleration(a_);
      rigidPolygon.setVertices(vertices_);

      EXPECT_EQ(rigidPolygon.getCurveType(), CurveType2D::PolygonType);
      EXPECT_EQ(rigidPolygon.getVertexCount(), vertexCount);
      for (int i = 0; i < vertexCount; ++i) {
        EXPECT_EQ(rigidPolygon.getVertex(i), vertices_[i]);
      }
      EXPECT_EQ(rigidPolygon.getMass(), mass);
      EXPECT_EQ(rigidPolygon.getPosition(), s_);
      EXPECT_EQ(rigidPolygon.getVelocity(), v_);
      EXPECT_EQ(rigidPolygon.getAcceleration(), a_);
    }
  }
}
