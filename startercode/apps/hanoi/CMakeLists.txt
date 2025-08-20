cmake_minimum_required(VERSION 2.4)

#set the project name
project(hanoi)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

#add the executable
add_executable(hanoi hanoi.cpp)

add_executable(hanoiit hanoiit.cpp)


