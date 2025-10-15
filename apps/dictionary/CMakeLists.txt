cmake_minimum_required(VERSION 3.11)

#set the project name
project(TestDictionary)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source)

file(GLOB all_SRCS
  "../../include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/source/*.cpp"
  "${PROJECT_SOURCE_DIR}/*.cpp"
  )

# Do the required setup for CMake

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#add the executable
add_executable(TestDictionary ${all_SRCS})
target_link_libraries(TestDictionary gtest_main)

include(GoogleTest)
gtest_discover_tests(TestDictionary)

