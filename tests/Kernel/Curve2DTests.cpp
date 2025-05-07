#include "Kernel/Curve2D.hpp"
#include <gtest/gtest.h>
#include <random>

using Isaac::Kernel::Curve2D;
using Isaac::Kernel::CurveType2D;

class Curve2DTests : public ::testing::Test {
protected:
  std::random_device rd;
  std::mt19937 x;

  void SetUp() override {
    std::random_device rd{};
    std::mt19937 x{rd()};
  }

  void TearDown() override {}
};

TEST_F(Curve2DTests, Constructors) {
  std::normal_distribution f{-1E300, 1E300};

  // CurveType2D::CircleType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Curve2D curve(CurveType2D::CircleType, s, v, a);

      Curve2D curve_(curve);
    }
  }

  // CurveType2D::PolygonType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Curve2D curve(CurveType2D::PolygonType, s, v, a);

      Curve2D curve_(curve);
    }
  }
}

TEST_F(Curve2DTests, Getters) {
  std::normal_distribution f{-1E300, 1E300};

  // CurveType2D::CircleType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Curve2D curve(CurveType2D::CircleType, s, v, a);

      EXPECT_EQ(curve.getCurveType(), CurveType2D::CircleType);
      EXPECT_EQ(curve.getPosition(), s);
      EXPECT_EQ(curve.getVelocity(), v);
      EXPECT_EQ(curve.getAcceleration(), a);
    }
  }

  // CurveType2D::PolygonType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Curve2D curve(CurveType2D::PolygonType, s, v, a);

      EXPECT_EQ(curve.getCurveType(), CurveType2D::PolygonType);
      EXPECT_EQ(curve.getPosition(), s);
      EXPECT_EQ(curve.getVelocity(), v);
      EXPECT_EQ(curve.getAcceleration(), a);
    }
  }
}

TEST_F(Curve2DTests, Setters) {
  std::normal_distribution f{-1E300, 1E300};

  // CurveType2D::CircleType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Curve2D curve(CurveType2D::CircleType, s, v, a);

      Vector2d s_ = {f(x), f(x)};
      Vector2d v_ = {f(x), f(x)};
      Vector2d a_ = {f(x), f(x)};

      curve.setPosition(s_);
      curve.setVelocity(v_);
      curve.setAcceleration(a_);

      EXPECT_EQ(curve.getPosition(), s_);
      EXPECT_EQ(curve.getVelocity(), v_);
      EXPECT_EQ(curve.getAcceleration(), a_);

      EXPECT_NE(s_, s);
      EXPECT_NE(v_, v);
      EXPECT_NE(a_, a);
    }
  }

  // CurveType2D::PolygonType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector2d s = {f(x), f(x)};
      Vector2d v = {f(x), f(x)};
      Vector2d a = {f(x), f(x)};

      Curve2D curve(CurveType2D::PolygonType, s, v, a);

      Vector2d s_ = {f(x), f(x)};
      Vector2d v_ = {f(x), f(x)};
      Vector2d a_ = {f(x), f(x)};

      curve.setPosition(s_);
      curve.setVelocity(v_);
      curve.setAcceleration(a_);

      EXPECT_EQ(curve.getPosition(), s_);
      EXPECT_EQ(curve.getVelocity(), v_);
      EXPECT_EQ(curve.getAcceleration(), a_);

      EXPECT_NE(s_, s);
      EXPECT_NE(v_, v);
      EXPECT_NE(a_, a);
    }
  }
}
