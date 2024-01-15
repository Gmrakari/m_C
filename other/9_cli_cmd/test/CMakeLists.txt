# test/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

project(cli_cmd_app C)

# 添加主目录下的 CMakeLists.txt
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/project_dir)

# 包含头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/test/include
    ${PROJECT_SOURCE_DIR}/cli_cmd_lib/include
)

set(CMAKE_BUILD_TYPE Debug)

# 启用调试信息
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

file(GLOB_RECURSE SRC_LISTS "src/*.c"
                            main.c
)

# 创建可执行文件
add_executable(cli_cmd_app ${SRC_LISTS})

# 链接主项目生成的动态库
target_link_libraries(cli_cmd_app PRIVATE cli_cmd_lib)

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
