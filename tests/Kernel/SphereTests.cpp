#include "Kernel/Sphere.hpp"
#include <gtest/gtest.h>
#include <random>

using Isaac::Kernel::Sphere;

class SphereTests : public ::testing::Test {
protected:
  std::random_device rd;
  std::mt19937 x;

  void SetUp() override {
    std::random_device rd{};
    std::mt19937 x{rd()};
  }

  void TearDown() override {}
};

TEST_F(SphereTests, Constructor) {
  std::normal_distribution f{-1E300, 1E300};
  std::normal_distribution R{1E-300, 1E300};

  for (int t = 1; t <= 1'00'000; ++t) {
    double r = R(x);
    Vector3d s = {f(x), f(x), f(x)};
    Vector3d v = {f(x), f(x), f(x)};
    Vector3d a = {f(x), f(x), f(x)};

    Sphere sphere(r, s, v, a);

    Sphere sphere_(sphere);
  }
}

TEST_F(SphereTests, Getters) {
  std::normal_distribution f{-1E300, 1E300};
  std::normal_distribution R{1E-300, 1E300};

  for (int t = 1; t <= 1'00'000; ++t) {
    double r = R(x);
    Vector3d s = {f(x), f(x), f(x)};
    Vector3d v = {f(x), f(x), f(x)};
    Vector3d a = {f(x), f(x), f(x)};

    Sphere sphere(r, s, v, a);

    EXPECT_EQ(sphere.getRadius(), r);
  }
}
