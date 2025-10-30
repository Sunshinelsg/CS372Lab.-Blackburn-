cmake_minimum_required(VERSION 3.11)

#set the project name
project(AVLTreeDemo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

#add the executable
add_executable(avltree avltree.cpp)
add_executable(main main.cpp)


