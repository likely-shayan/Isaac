#include "Kernel/Curve3D.hpp"
#include <gtest/gtest.h>
#include <random>

using Isaac::Kernel::Curve3D;
using Isaac::Kernel::CurveType3D;

class Curve3DTests : public ::testing::Test {
protected:
  std::random_device rd;
  std::mt19937 x;

  void SetUp() override {
    std::random_device rd{};
    std::mt19937 x{rd()};
  }

  void TearDown() override {}
};

TEST_F(Curve3DTests, Constructors) {
  std::normal_distribution f{-1E300, 1E300};

  // CurveType3D::SphereType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector3d s = {f(x), f(x), f(x)};
      Vector3d v = {f(x), f(x), f(x)};
      Vector3d a = {f(x), f(x), f(x)};

      Curve3D curve(CurveType3D::SphereType, s, v, a);

      Curve3D curve_(curve);
    }
  }
}

TEST_F(Curve3DTests, Getters) {
  std::normal_distribution f{-1E300, 1E300};

  // CurveType3D::SphereType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector3d s = {f(x), f(x), f(x)};
      Vector3d v = {f(x), f(x), f(x)};
      Vector3d a = {f(x), f(x), f(x)};

      Curve3D curve(CurveType3D::SphereType, s, v, a);

      EXPECT_EQ(curve.getCurveType(), CurveType3D::SphereType);
      EXPECT_EQ(curve.getPosition(), s);
      EXPECT_EQ(curve.getVelocity(), v);
      EXPECT_EQ(curve.getAcceleration(), a);
    }
  }
}

TEST_F(Curve3DTests, Setters) {
  std::normal_distribution f{-1E300, 1E300};

  // CurveType3D::SphereType
  {
    for (int t = 1; t <= 1'00'000; ++t) {
      Vector3d s = {f(x), f(x), f(x)};
      Vector3d v = {f(x), f(x), f(x)};
      Vector3d a = {f(x), f(x), f(x)};

      Curve3D curve(CurveType3D::SphereType, s, v, a);

      Vector3d s_ = {f(x), f(x), f(x)};
      Vector3d v_ = {f(x), f(x), f(x)};
      Vector3d a_ = {f(x), f(x), f(x)};

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
