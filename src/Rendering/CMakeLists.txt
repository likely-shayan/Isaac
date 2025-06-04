add_library(Isaac_Rendering
  Window.cpp
)

target_include_directories(Isaac_Rendering
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

include(FetchContent)

find_package(OpenGL REQUIRED)

find_package(glfw 3.4 CONFIG QUIET)
if (glfw_FOUND)
  message(STATUS "Found glfw3")
else()
  message(STATUS "glfw not found, fetching via FetchContent...")
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
    GIT_PROGRESS  TRUE
  )
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(glfw)
endif()

find_package(glad CONFIG QUIET)
if (glad_FOUND)
  message(STATUS "Found glad")
  set(GLAD_FOUND TRUE)
else()
  message(STATUS "glad not found, fetching via FetchContent...")
  FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad
    GIT_TAG v2.0.8
    GIT_SHALLOW TRUE
    GIT_PROGRESS  TRUE
  )
  FetchContent_GetProperties(glad)
  if(NOT glad_POPULATED)
      message("Fetching glad")
      set(GLAD_BUILD_TESTS OFF CACHE BOOL "" FORCE)
      set(GLAD_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
      FetchContent_MakeAvailable(glad)
      add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
      glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6 EXTENSIONS GL_ARB_bindless_texture GL_EXT_texture_compression_s3tc)
  endif()
  set(GLAD_FOUND FALSE)
endif()

target_link_libraries(Isaac_Rendering
  PUBLIC
  glfw
  glad
  OpenGL::GL
)