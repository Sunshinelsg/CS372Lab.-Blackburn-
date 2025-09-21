cmake_minimum_required(VERSION 3.10)

#set the project name
project(simplecalc)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../include)

#add the executable
add_executable(simplecalc simplecalc.cpp)

