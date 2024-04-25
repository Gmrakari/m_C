# cmake_minimum_required(VERSION 3.0)

# project(fifo C)

# # 包含头文件目录
# include_directories(
#     ${PROJECT_SOURCE_DIR}/.
# )

# set(CMAKE_BUILD_TYPE Debug)

# # 启用调试信息
# set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

# file(GLOB_RECURSE SRC_LISTS "./*.c"
#                             main.c
# )

# # 创建可执行文件
# add_executable(fifo_app ${SRC_LISTS})

# # 设置可执行文件输出路径
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

cmake_minimum_required(VERSION 3.1)

project(fifo C)

# include_directories(${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE SRC_LISTS "*.c")

# add_executable(fifp_app ${SRC_LISTS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# add_executable(fifo_app ${SRC_LISTS})
add_executable(fifo_app main.c ring_buffer.c)
