# 1. set version
# 2. set project name
# 3. set include directory
# 4. set source file
# 5. generate execuate file
# 6. generate output exe file

cmake_minimum_required(VERSION 3.0)

# 声明库，将生成一个共享库或静态库
project(c_lib)

# 设置 C 语言标准
set(CMAKE_C_STANDARD 11)

# 添加库的头文件路径
include_directories(include)

# 查找源文件
file(GLOB LIB_SRC "src/*.c")

# 创建库
add_library(c_lib ${LIB_SRC})

# 链接信号量库
target_link_libraries(c_lib PRIVATE rt pthread)

# 如果需要，可以添加其他编译选项
target_compile_options(c_lib PRIVATE -fPIC)
