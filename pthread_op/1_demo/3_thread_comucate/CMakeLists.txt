cmake_minimum_required(VERSION 3.1)

project(3_multi_pthread C)

set(CMAKE_C_FLAGS -pthread)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE src_dir_list "src/*c")

add_executable(3_multi-pthread ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
