include(FetchContent)

find_package(GTest CONFIG QUIET)
if(NOT GTest_FOUND)
  message(STATUS "GTest not found, fetching via FetchContent...")
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.14.0
  )
  set(gtest_build_samples OFF CACHE BOOL "" FORCE)
  set(gtest_build_tests OFF CACHE BOOL "" FORCE)
  set(gmock_build_tests OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()
message(STATUS "GTest found or fetched.")

add_executable(Isaac_Kernel_Tests
    Curves2DTests.cpp
    Circle2DTests.cpp
)

target_include_directories(Isaac_Kernel_Tests
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(Isaac_Kernel_Tests
    PRIVATE
        Isaac_Kernel
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(Isaac_Kernel_Tests)