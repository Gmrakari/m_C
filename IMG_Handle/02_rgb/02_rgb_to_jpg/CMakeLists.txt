cmake_minimum_required(VERSION 3.10)
project(app C)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/libjpeg/include
)

# JPEG 库源文件和头文件
file(GLOB JPEG_SOURCES ${PROJECT_SOURCE_DIR}/libjpeg/source/*.c)
file(GLOB JPEG_HEADERS ${PROJECT_SOURCE_DIR}/libjpeg/include/*.h)

# 创建 JPEG 库
add_library(jpeg ${JPEG_SOURCES} ${JPEG_HEADERS})

# 设置源文件
set(SOURCES
  ${PROJECT_SOURCE_DIR}/src/main.c
  ${PROJECT_SOURCE_DIR}/src/rgb_to_jpg.c
  ${PROJECT_SOURCE_DIR}/libjpeg/libjpeg.c
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 链接 JPEG 库
target_link_libraries(${PROJECT_NAME} jpeg)

# 添加测试
enable_testing()

add_test(
    NAME MemoryLeakTest
    COMMAND valgrind --leak-check=full --track-origins=yes $<TARGET_FILE:app>
)

