cmake_minimum_required(VERSION 3.0)

project(file_api_usage C)

file(GLOB SRCS "./*.c")

add_executable(file_api_usage fopen.c ${SRCS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)