cmake_minimum_required(VERSION 3.1)

project(callback_take_out_parm C)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE src_dir_list "src/*c")

add_executable(callback_take_out_param ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)