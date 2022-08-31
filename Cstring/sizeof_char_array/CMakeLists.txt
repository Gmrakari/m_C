# setting camke min version
cmake_minimum_required(VERSION 3.2)

# setting project name
project(sizeof_char_array C)

# setting c source file
FILE(GLOB_RECURSE SRC_DIR_LIST "src/*.c")

# setting execute bin name
add_executable (sizeofCharArray ${SRC_DIR_LIST})

# setting output directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

