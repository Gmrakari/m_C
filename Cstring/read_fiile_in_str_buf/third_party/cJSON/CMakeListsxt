cmake_minimum_required(VERSION 3.0)

# 设置库名
set(LIB_NAME cJsonlib)

# 设置头文件目录
set(CJSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)  

# 添加源文件
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_library(cJsonlib SHARED ${SOURCE_FILES})

set_target_properties(cJsonlib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
