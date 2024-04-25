cmake_minimum_required(VERSION 3.0)

project(base64 C)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(base64_app main.c gm_base64.c)

