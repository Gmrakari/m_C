cmake_minimum_required(VERSION 3.5)

project(qrcode)

# 设置C编译器
set(CMAKE_C_COMPILER gcc)

# 添加头文件路径
include_directories(include third_party)

file(GLOB_RECURSE SRC_LISTS "src/*.c")

set(STATIC_LIB_NAME qrcode_static)
set(STATIC_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SHARED_LIB_NAME qrcode_shared)
set(SHARED_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 添加静态库和动态库生成路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 生成静态库
add_library(${STATIC_LIB_NAME} STATIC ${SRC_LISTS})

# 生成动态库
add_library(${SHARED_LIB_NAME} SHARED ${SRC_LISTS})

# 设置动态库的版本号
# set_target_properties(qrcode_shared PROPERTIES VERSION 1.0)
set_target_properties(${STATIC_LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${STATIC_LIB_DIR})
set_target_properties(${SHARED_LIB_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${SHARED_LIB_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 生成可执行文件
add_executable(qrcode_app main.c)

# 链接生成的静态库或动态库
target_link_libraries(qrcode_app qrcode_static)
