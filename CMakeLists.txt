cmake_minimum_required(VERSION 3.11)

project(Isaac)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/Kernel)
add_subdirectory(src/Rendering)

add_executable(${PROJECT_NAME}
  src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Isaac_Kernel
  Isaac_Rendering
)