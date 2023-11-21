# old setting
# cmake_minimum_required(VERSION 3.1)

# project(execl C)

# # set(CMAKE_C_FLAGS -)

# include_directories(${PROJECT_SOURCE_DIR}/include)

# file(GLOB_RECURSE src_dir_list "src/*c")

# add_executable(execl ${src_dir_list})

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# new setting

cmake_minimum_required(VERSION 3.0)

project(execl C)

file(GLOB_RECURSE src_dir_list "src/*c")

add_executable(app main.c ${src_dir_list})

# 添加头文件目录
target_include_directories(app PRIVATE include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
