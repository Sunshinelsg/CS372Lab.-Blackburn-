cmake_minimum_required(VERSION 3.10)

#set the project name
project(clisttest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

# Add the executable for a simple test using main()
add_executable(clisttest clisttest.cpp)

# Enable testing with Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_clisttest test_clisttest.cpp)
target_link_libraries(test_clisttest gtest gtest_main pthread)
add_test(NAME CircularListTest COMMAND test_clisttest)