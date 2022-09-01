cmake_minimum_required(VERSION 3.5)

project(mtakeSubString C)

file(GLOB_RECURSE src_dir_list "src/*c")

add_executable(mtakeSubString ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)