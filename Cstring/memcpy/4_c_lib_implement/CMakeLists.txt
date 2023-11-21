cmake_minimum_required(VERSION 3.0)

project(c_lib C)

set(CMAKE_C_STANDARD 99)

add_executable(app main.c)

add_subdirectory(c_lib)

target_link_libraries(app PRIVATE c_lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# target_compile_options(main PRIVATE -lpthread -lrt)
