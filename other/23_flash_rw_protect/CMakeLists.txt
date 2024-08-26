cmake_minimum_required(VERSION 3.0)

project(app)

set(CMAKE_C_STANDARD 99)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

file(GLOB_RECURSE SRC_LIST "src/*.c")

add_executable(${PROJECT_NAME} main.c ${SRC_LIST})

# link .a || .so

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include(CTest)

add_test(NAME valgrind_test
         COMMAND valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 $<TARGET_FILE:${PROJECT_NAME}>)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
endif()