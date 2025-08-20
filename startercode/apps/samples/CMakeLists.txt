cmake_minimum_required(VERSION 2.8)

#set the project name
project(assignment01)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source)

file(GLOB all_SRCS
  "../../include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/source/*.cpp"
  "${PROJECT_SOURCE_DIR}/soruce/*.cpp"
  )

#add the executable
add_executable(fibtime fibtime.cpp)

