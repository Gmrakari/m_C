cmake_minimum_required(VERSION 3.10)
project(cjson_lib C)

# 查找源文件和头文件
file(GLOB cJSON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB cJSON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# 添加静态库和共享库，并显式指定语言
add_library(cjson_static STATIC ${cJSON_SOURCES})
add_library(cjson_shared SHARED ${cJSON_SOURCES})

set_target_properties(cjson_static PROPERTIES LINKER_LANGUAGE C)
set_target_properties(cjson_shared PROPERTIES LINKER_LANGUAGE C)

# 包含目录
target_include_directories(cjson_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(cjson_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 指定输出目录
set_target_properties(cjson_static PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

set_target_properties(cjson_shared PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# 安装目标
install(TARGETS cjson_static
        ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib)

install(TARGETS cjson_shared
        LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 安装头文件
install(FILES ${cJSON_HEADERS} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)
