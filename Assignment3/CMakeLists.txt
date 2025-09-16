cmake_minimum_required(VERSION 3.12)

# Set the project name
project(Assignment3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include current directory so headers like assignbag3.hpp can be found
include_directories(${PROJECT_SOURCE_DIR})

# Collect all source files
file(GLOB all_SRCS
  "${PROJECT_SOURCE_DIR}/*.cpp"
  "${PROJECT_SOURCE_DIR}/*.hpp"
)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Build the executable with test source files
add_executable(Assignment3 ${all_SRCS})
target_link_libraries(Assignment3 gtest_main)

# Enable test discovery
include(GoogleTest)
gtest_discover_tests(Assignment3)