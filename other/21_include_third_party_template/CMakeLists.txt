cmake_minimum_required(VERSION 3.10)

# 项目信息
project(MyProject C)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)

# 添加子目录
add_subdirectory(third_party/cjson)
# add_subdirectory(src)

# 包含目录
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/third_party/cjson/include)

# 可执行文件
add_executable(my_app main.c)

# 链接库
target_link_libraries(my_app cjson_lib)
