#include <gtest/gtest.h>
#include <random>
#include "Kernel/Circle2D.hpp"

using namespace Isaac::Kernel;

class Circle2DTests : public ::testing::Test {
protected:
  std::random_device rd;
  std::mt19937 x;

  void SetUp() override {
    std::random_device rd{};
    std::mt19937 x{rd()};
  }

  void TearDown() override {}
};

TEST_F(Circle2DTests, Constructor) {
  std::normal_distribution f{-1E300, 1E300};
  std::normal_distribution R{1E-300, 1E300};

  for (int t = 1; t <= 1'00'000; ++t) {
    double r = R(x);
    Vector2d s = {f(x), f(x)};
    Vector2d v = {f(x), f(x)};
    Vector2d a = {f(x), f(x)};

    Circle2D circle(r, s, v, a);

    Circle2D circle_(circle);
  }
}

TEST_F(Circle2DTests, Getters) {
  std::normal_distribution f{-1E300, 1E300};
  std::normal_distribution R{1E-300, 1E300};

  for (int t = 1; t <= 1'00'000; ++t) {
    double r = R(x);
    Vector2d s = {f(x), f(x)};
    Vector2d v = {f(x), f(x)};
    Vector2d a = {f(x), f(x)};

    Circle2D circle(r, s, v, a);

    EXPECT_EQ(circle.getRadius(), r);
  }
}