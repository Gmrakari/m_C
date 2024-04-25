cmake_minimum_required(VERSION 3.0)

project(struct_arr_app C)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_LISTS "src/*.c")

add_executable(${PROJECT_NAME} ${SRC_LISTS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
