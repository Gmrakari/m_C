cmake_minimum_required(VERSION 3.0)

project(app C)

include_directories(${PROJECT_SOURCE_DIR}/inc)

file(GLOB_RECURSE src_dir_list "src/*c" "main.c")

add_executable(${PROJECT_NAME} ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
