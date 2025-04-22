# Minimum version of CMake required
cmake_minimum_required(VERSION 3.30)

# Name of project
project(Isaac)

# Minimum version of C++ required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Finding and including Eigen library
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# Add source files
add_library(Isaac_Kernel
  src/Shapes.cpp
  src/Circles.cpp
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
  Isaac_Kernel
  Eigen3::Eigen
)