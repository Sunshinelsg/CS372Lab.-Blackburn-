cmake_minimum_required(VERSION 3.11)

#set the project name
project(HeapDemo)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../include)

#add the executable
add_executable(heapstl heapstl.cpp)

add_executable(pq pq.cpp)
