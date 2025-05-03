add_library(Isaac_Kernel

    # 2D Parent and Child Classes
    Curve2D.cpp
    Circle.cpp

    # 3D Parent and Child Classes
    Curve3D.cpp
    Sphere.cpp

)

target_include_directories(Isaac_Kernel
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

include(FetchContent)

find_package(Eigen3 3.3 CONFIG QUIET HINTS ${EIGEN_ROOT})
if(Eigen3_FOUND)
  message(STATUS "Found Eigen3")
  set(EIGEN_FOUND TRUE)
else()
  message(STATUS "Eigen3 not found, fetching via FetchContent...")
  FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG master
  )
  set(EIGEN_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(EIGEN_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(EIGEN_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(EIGEN_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
  set(EIGEN_INSTALL_EXAMPLES OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(eigen)
set(EIGEN_FOUND FALSE)
endif()

target_link_libraries(Isaac_Kernel
    PUBLIC
    Eigen3::Eigen
)