# Minimum version of CMake required
cmake_minimum_required(VERSION 3.30)

# Name of project
project(Isaac)

option(ENABLE_TESTS "Enable building of tests" ON)

# Minimum version of C++ required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent to install and set up libraries
include(FetchContent)

# Search if Eigen is already available
find_package(Eigen3 3.3 CONFIG QUIET HINTS ${EIGEN_ROOT})

# Eigen is already available
if(Eigen3_FOUND)
  message(STATUS "Found Eigen3")
  set(EIGEN_FOUND TRUE)

# Eigen is not installed
else()
  message(STATUS "Eigen3 not found, fetching via FetchContent...")

  # Installing and Setting up Eigen using FetchContent
  FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG master
  )

  # Disable Building of tests, docs and examples of Eigen
  set(EIGEN_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(EIGEN_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(EIGEN_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(EIGEN_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
  set(EIGEN_INSTALL_EXAMPLES OFF CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(eigen)

set(EIGEN_FOUND FALSE)
endif()

# Add source files
add_library(Isaac_Kernel
  src/Kernel/Curves2D.cpp
)

# Add header files
target_include_directories(Isaac_Kernel
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# The main executable file
add_executable(${PROJECT_NAME}
  src/main.cpp
)

# Linking all the libraries together
target_link_libraries(${PROJECT_NAME}
  PRIVATE
  Isaac_Kernel
  Eigen3::Eigen
)

if (ENABLE_TESTS)
  enable_testing()

  # Check if GTest is already available
  find_package(GTest CONFIG QUIET)

  # GTest was already available
  if(GTest_FOUND)
    message(STATUS "Found GTest")
    set(GTEST_FOUND TRUE)

  # GTest was not already available
  else()
    message(STATUS "GTest not found, fetching via FetchContent...")
    
    # Installing and setting up GTest using FetchContent
    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG v1.16.0
    )

    # Disable building tests, docs and examples of GTest
    set(gtest_build_samples OFF CACHE BOOL "" FORCE)
    set(gtest_build_advanced_samples OFF CACHE BOOL "" FORCE)
    set(gtest_build_gmock OFF CACHE BOOL "" FORCE) # If you only need gtest
    set(gtest_build_gmock_samples OFF CACHE BOOL "" FORCE) # If you only need gtest
    set(gtest_disable_pthreads OFF CACHE BOOL "" FORCE) # Or ON if you have issues
    set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE) # Adjust as needed

    FetchContent_MakeAvailable(googletest)
    set(GTEST_FOUND FALSE) # Indicate it's from FetchContent
  endif()

  # Adding all test files for Mathematical Objects
  # add_executable(Isaac_Mathematical_Objects_Tests)

  # Linking libraries for test of Mathematical Objects
  # target_link_libraries(Isaac_Mathematical_Objects_Tests
  #   PRIVATE
  #   Isaac_Kernel
  #   Eigen3::Eigen
  #   gtest
  #   gtest_main
  # )

  # Add test file for Mathematical Objects
  # add_test(NAME Isaac_Mathematical_Objects_Tests COMMAND Isaac_Mathematical_Objects_Tests)

endif()