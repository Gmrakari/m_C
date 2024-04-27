cmake_minimum_required(VERSION 3.0)

project(linklist C)

set(CMAKE_C_STANDARD 99)

add_executable(app main.c)

add_subdirectory(source)

target_link_libraries(app PRIVATE linklistlib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)