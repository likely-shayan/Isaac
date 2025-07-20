add_library(Isaac_Kernel
        Polygon.cpp
        Mesh.cpp
)

find_package(Eigen3 3.4.0 CONFIG QUIET)
if (Eigen3_FOUND)
    message(STATUS "Found Eigen3")
else()
    message(STATUS "Eigen3 not found, fetching via FetchContent...")
    include(FetchContent)
    FetchContent_Declare(
            Eigen
            GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
            GIT_TAG 3.4.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    set(Eigen3_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(Eigen3_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(Eigen3_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(Eigen)
endif()

target_link_libraries(Isaac_Kernel PUBLIC Eigen3::Eigen)

target_include_directories(Isaac_Kernel
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)