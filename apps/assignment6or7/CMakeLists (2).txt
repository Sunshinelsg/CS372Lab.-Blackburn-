cmake_minimum_required(VERSION 3.8)

#set the project name
project(treetest)

set(CMAKE_CXX_STANDARD 17)

# Get the stuff we need to use Google Test...
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(../../include ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add the executable, now for using Google Test
add_executable(treetest treetest.cpp ../../include/Tree.hpp)
target_link_libraries(treetest GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(treetest)