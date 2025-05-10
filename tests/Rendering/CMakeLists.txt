include(FetchContent)

find_package(GTest CONFIG QUIET)
if (GTest_FOUND)
    message(STATUS "Found GTest.")
else()
    message(STATUS "GTest not found, fetching via FetchContent...")
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.14.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS  TRUE
    )
    set(gtest_build_samples OFF CACHE BOOL "" FORCE)
    set(gtest_build_tests OFF CACHE BOOL "" FORCE)
    set(gmock_build_tests OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(Isaac_Rendering_Tests
        Renderable_Object_2D_Tests.cpp
)

target_include_directories(Isaac_Rendering_Tests
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Isaac_Rendering_Tests
        PRIVATE
        Isaac_Kernel
        Isaac_Rendering
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Isaac_Rendering_Tests)