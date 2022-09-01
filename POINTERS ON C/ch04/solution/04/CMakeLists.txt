cmake_minimum_required(VERSION 3.2)

project(copy_n C)

file(GLOB_RECURSE src_dir_list "src/*c")

add_executable(copy_n ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)