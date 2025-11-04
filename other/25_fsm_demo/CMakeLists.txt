cmake_minimum_required(VERSION 3.10)

project(app C)

# 添加头文件路径
include_directories(
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/src
    ${OPENSSL_INCLUDE_DIR}
)

# 获取所有源文件
file(GLOB_RECURSE src_dir_list 
    "src/*.c" 
    "main.c"
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${src_dir_list})

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
