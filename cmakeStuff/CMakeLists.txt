cmake_minimum_required(VERSION 3.10)
project(MyProgram)

# Automatically find all .cpp files recursively in this directory
file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(my_program ${SOURCES})
