cmake_minimum_required(VERSION 3.0)

project(app)

set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc 
                    ${CMAKE_CURRENT_SOURCE_DIR}/utils/include 
                   ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cjson/include)


add_subdirectory(third_party)

file(GLOB_RECURSE SRC_LIST "src/*.c" "utils/src/*.c")

add_executable(${PROJECT_NAME} main.c ${SRC_LIST})

# link .a || .so
target_link_libraries(${PROJECT_NAME} cjson_static)
# target_link_libraries(my_app cjson_shared)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include(CTest)

add_test(NAME valgrind_test
         COMMAND valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 $<TARGET_FILE:${PROJECT_NAME}>)
