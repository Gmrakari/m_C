cmake_minimum_required(VERSION 3.0)

project(app C)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/inc
)

include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES
    "src/*.c"
    "main.c"
)

file(GLOB_RECURSE SRC_LISTS ${SOURCE_FILES})

add_executable(${PROJECT_NAME} ${SRC_LISTS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

target_compile_options(${PROJECT_NAME} PRIVATE -lpthread)

include(CTest)

if(COMMAND valgrind)
    add_test(NAME valgrind_test
             COMMAND valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 $<TARGET_FILE:${PROJECT_NAME}>)
else()
    message(WARNING "Valgrind not found. Memory leak tests will be skipped.")
endif()

