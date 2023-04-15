cmake_minimum_required(VERSION 3.10)
project(my_project)

# 添加子目录
add_subdirectory(utils/http)
add_subdirectory(test)

# 添加可执行文件
add_executable(my_project main.c)

# 链接http_get库
target_link_libraries(my_project http_get)

# 设置安装路径
install(TARGETS my_project DESTINATION bin)
