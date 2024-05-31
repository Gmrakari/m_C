cmake_minimum_required(VERSION 3.0)

project(reactor_server_app)

set(CMAKE_C_COMPILER gcc)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRCS "src/*.c")

add_executable(${PROJECT_NAME} ${SRCS} main.c)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
