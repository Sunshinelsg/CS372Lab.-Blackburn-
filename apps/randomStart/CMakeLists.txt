cmake_minimum_required(VERSION 3.11)

#set the project name
project(randomtest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/../../include)

#Add executable
add_executable(randomStart 
	randomStart.cpp 
	${CMAKE_SOURCE_DIR}/../../src/random.cpp
	)