cmake_minimum_required(VERSION 3.0)

project(sscanf C)

include_directories(${PROJECT_SOURCE_DIR}/include)

# aux_source_directory(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE src_dir_list "src/*c")

add_executable(sscanf_app ${src_dir_list} main.c)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)