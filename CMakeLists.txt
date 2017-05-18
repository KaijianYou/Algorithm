cmake_minimum_required(VERSION 3.6)
project(Algorithm)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-Wall -O2)

set(SOURCE_FILES main.cpp algorithm/encrypt/base64.h)
add_executable(Algorithm ${SOURCE_FILES})