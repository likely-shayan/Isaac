cmake_minimum_required(VERSION 3.30)
project(Isaac)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(IsaacLib
  src/vector2d.cpp
  src/vector3d.cpp
)

target_include_directories(IsaacLib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(Isaac
  src/main.cpp
)

target_link_libraries(Isaac
  PRIVATE
  IsaacLib
)