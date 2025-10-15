cmake_minimum_required(VERSION 3.11)

#set the project name
project(ExpTreeDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

#add the executable
add_executable(exptree ExpTree.cpp)


