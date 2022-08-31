cmake_minimum_required(VERSION 3.2)

project(calc_square C)

file(GLOB_RECURSE src_dir_list "src/*c")

add_executable(calc_square ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)