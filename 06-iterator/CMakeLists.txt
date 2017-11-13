cmake_minimum_required(VERSION 3.8)
project(06_iterator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES  List.h List.cpp main.cpp )

add_executable(06_iterator ${SOURCE_FILES})