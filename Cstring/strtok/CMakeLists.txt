cmake_minimum_required(VERSION 3.0)

project(strtok_app C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(strtok_app main.c ${SRCS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)