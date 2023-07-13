cmake_minimum_required(VERSION 3.2)

project(log_test C)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_LIST "src/*c")

add_executable(log_test_app ${SRC_LIST})

# 为log_test_app目标添加include目录
target_include_directories(log_test_app PRIVATE ${PROJECT_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
