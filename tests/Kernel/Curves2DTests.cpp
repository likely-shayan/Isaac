#include <gtest/gtest.h>
#include "Kernel/Curves2D.hpp"

using namespace Isaac::Kernel;

class Curves2DTests : public ::testing::Test {

  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(Curves2DTests, Constructors_Getters_Setters_Test) {

  Curve2D baseCase(CurveTypes2D::Circle2D, {0, 0}, {0, 0}, {0, 0});
  EXPECT_EQ(baseCase.getCurveType(), CurveTypes2D::Circle2D);
  EXPECT_EQ(baseCase.getPosition(), Vector2d(0, 0));
  EXPECT_EQ(baseCase.getVelocity(), Vector2d(0, 0));
  EXPECT_EQ(baseCase.getAcceleration(), Vector2d(0, 0));


  baseCase.setPosition({1, 2});
  baseCase.setVelocity({3, 4});
  baseCase.setAcceleration({5, 6});
  EXPECT_EQ(baseCase.getCurveType(), CurveTypes2D::Circle2D);
  EXPECT_EQ(baseCase.getPosition(), Vector2d(1, 2));
  EXPECT_EQ(baseCase.getVelocity(), Vector2d(3, 4));
  EXPECT_EQ(baseCase.getAcceleration(), Vector2d(5, 6));
}