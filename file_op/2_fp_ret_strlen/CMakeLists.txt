cmake_minimum_required(VERSION 3.0)

project(read_file_string_len_app C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
