cmake_minimum_required(VERSION 3.0)

project(strTocJSON C)

include_directories(${PROJECT_SOURCE_DIR}/include)

# 添加主项目源文件
file(GLOB MAIN_SRC ${PROJECT_SOURCE_DIR}/main.c)

# 添加 src 目录下的源文件
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

# 添加 cJSON 目录下的源文件
file(GLOB cJSON_SRC ${PROJECT_SOURCE_DIR}/third_party/cJSON/src/*.c)

# 生成动态库
add_library(cJsonlib SHARED ${SRC_FILES} ${cJSON_SRC})

# 设置库的输出目录
set_target_properties(cJsonlib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/third_party/cJSON/lib)

# 添加可执行文件并链接库
add_executable(strTocJSONApp ${MAIN_SRC})

# 链接 cJSON 库
target_link_libraries(strTocJSONApp PRIVATE cJsonlib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
