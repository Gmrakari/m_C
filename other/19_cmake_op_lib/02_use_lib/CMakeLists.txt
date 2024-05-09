cmake_minimum_required(VERSION 3.0)

project(use_lib_app C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} main.c)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 查找库
file(GLOB LIBS ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.a)

# 追加库
target_link_libraries(${PROJECT_NAME} PRIVATE PRIVATE ${LIBS})
