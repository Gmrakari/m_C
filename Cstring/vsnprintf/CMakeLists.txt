cmake_minimum_required(VERSION 3.0)

project(vsnprintf_app C)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_SRC "src/*c")

add_executable(vsnprintf_app main.c ${SOURCE_SRC})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)