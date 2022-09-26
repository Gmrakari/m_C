cmake_minimum_required(VERSION 3.5)

project(encpyStr C)

file(GLOB_RECURSE SRC_DIR_LIST "src/*c")

add_executable(encpyStr ${SRC_DIR_LIST})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)