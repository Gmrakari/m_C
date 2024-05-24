cmake_minimum_required(VERSION 3.0)

project(4k_db C)

include_directories(${PROJECT_SOURCE_DIR}/inc)

include_directories(${PROJECT_SOURCE_DIR}/utils)

file(GLOB_RECURSE src_dir_list "src/*c" "main.c")

add_executable(4k_tmp_passwd_db_app ${src_dir_list})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
