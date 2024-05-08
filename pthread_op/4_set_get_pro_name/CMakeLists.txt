cmake_minimum_required(VERSION 3.0)

project(pro_name)

set(CMAKE_C_COMPILER gcc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_LIST "src/*.c")

add_executable(app main.c ${SRC_LIST})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
