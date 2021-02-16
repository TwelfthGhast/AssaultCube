cmake_minimum_required(VERSION 3.16)
project(AssaultCube)

set(CMAKE_CXX_STANDARD 14)

add_executable(AssaultCube main.cpp utils/pid_util.cpp utils/util.h utils/hook_util.cpp)