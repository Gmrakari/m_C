cmake_minimum_required(VERSION 3.0)

project(http)

# 设置 C 编译器
set(CMAKE_C_COMPILER gcc)

# 添加子目录
add_subdirectory(utils/http)

# 添加可执行文件
add_executable(app main.c)

# 链接主程序和子目录中的库
target_link_libraries(app http_utils)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)