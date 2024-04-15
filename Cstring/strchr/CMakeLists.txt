cmake_minimum_required(VERSION 3.0)

project(strchr C)

set(SOURCES strchr_main.c)

# 创建可执行文件
add_executable(app ${SOURCES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
