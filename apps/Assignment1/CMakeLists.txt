cmake_minimum_required(VERSION 2.4)

#set the project name
project(Assignment1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

#add the executable
add_executable(assign1 assign1.cpp)

add_executable(assign1it assign1it.cpp)