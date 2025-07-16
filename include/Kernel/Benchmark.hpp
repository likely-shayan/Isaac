#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Case {
public:
  Case(const std::string &caseName_, const std::function<void()> &testFunction_) {
    caseName = caseName_;
    testFunction = testFunction_;
  }

  [[nodiscard]] std::string getName() const noexcept {
    return caseName;
  }

  [[nodiscard]] std::function<void()> getTestFunction() const noexcept {
    return testFunction;
  }

private:
  std::string caseName;
  std::function<void()> testFunction;
};

class Benchmark {
public:
  Benchmark(const std::string &operationName_, const std::vector<Case> &cases_, const int &iterations_) {
    operationName = operationName_;
    cases = cases_;
    iterations = iterations_;
  }

  void RunAndShow() const {
    std::map<std::chrono::duration<long, std::ratio<1, 1'000'000'000> >::rep, std::string> results;
    for (auto &case_: cases) {
      std::chrono::duration<long, std::ratio<1, 1000000000> >::rep average = 0;
      for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        case_.getTestFunction()();
        auto endTime = std::chrono::high_resolution_clock::now();
        average += (endTime - startTime).count();
      }
      average /= iterations;
      results[average] = case_.getName();
    }

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << operationName << std::endl;
    std::cout << "Case Name " << "\t\t\t" << "Average Clock Cycles" << std::endl;;
    for (auto &[averageTime, caseName]: results) {
      std::cout << caseName << "\t\t\t\t" << averageTime << std::endl;
    }
    std::cout << "--------------------------------------------------" << std::endl;
  }

private:
  std::string operationName;
  std::vector<Case> cases;
  int iterations;
};

#endif //BENCHMARK_H
