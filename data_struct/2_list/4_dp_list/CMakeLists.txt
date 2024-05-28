cmake_minimum_required(VERSION 3.0)

project(db_list_app C)

include_directories(${PROJECT_SOURCE_DIR}/inc)

include_directories(${PROJECT_SOURCE_DIR}/utils)

file(GLOB_RECURSE src_dir_list "src/*c" "main.c")

add_executable(${PROJECT_NAME} ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Include CTest
include(CTest)

# Add a test target using Valgrind
add_test(NAME valgrind_test
         COMMAND valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 $<TARGET_FILE:${PROJECT_NAME}>)