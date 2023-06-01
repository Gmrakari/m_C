cmake_minimum_required(VERSION 3.0)

project(my_memcpy C)

include_directories(${PROJECT_SOURCE_DIR}/include)

# setting c source file
FILE(GLOB_RECURSE SRC_DIR_LIST "src/*.c")

# setting execute bin name
add_executable (my_memcpy ${SRC_DIR_LIST})

# setting output directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

