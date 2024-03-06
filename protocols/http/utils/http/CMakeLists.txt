# 设置 C 编译器
set(CMAKE_C_COMPILER gcc)

# 添加头文件路径
include_directories(include)

# 查找 src 目录下的所有源文件
file(GLOB SOURCES "src/*.c")

# 添加源文件
add_library(http_utils STATIC ${SOURCES})

# 设置库的输出名称
set_target_properties(http_utils PROPERTIES OUTPUT_NAME "http_utils")

# 链接 OpenSSL 库
target_link_libraries(http_utils -lssl -lcrypto)

# 安装库文件和头文件
install(TARGETS http_utils DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
