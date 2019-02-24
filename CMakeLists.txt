cmake_minimum_required(VERSION 2.8.4)
project(cppstat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -L.")

# Generate shared library libCyclicBarrier.so file.
ADD_LIBRARY(cppstat SHARED winsor.cpp)

# Add test Examples below.
add_executable(Example1.out Example1.cpp)
target_link_libraries(Example1.out cppstat)
