cmake_minimum_required(VERSION 3.1)

project(syncCallBackFun C)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE src_dir_list "src/*c")

add_executable(syncCallBackFun ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
