cmake_minimum_required(VERSION 3.10)

project(app LANGUAGES C)

add_executable(app main.c)

add_subdirectory(demo)
add_subdirectory(threadpool)

# 包含其它库
target_include_directories(app
  PRIVATE 
    demo/include
    threadpool/include
)

# 链接lib
target_link_libraries(app
  demo
  threadpool
  pthread
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)