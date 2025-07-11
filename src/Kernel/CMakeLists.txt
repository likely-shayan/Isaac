add_library(Isaac_Kernel
        Vector.cpp
        Polygon.cpp
        Mesh.cpp
)

target_include_directories(Isaac_Kernel
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)