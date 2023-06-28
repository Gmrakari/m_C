cmake_minimum_required(VERSION 3.10)

project(struct_in_union_usage C)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE src_dir_list "src/*c")

add_executable(struct_in_union_usage ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)