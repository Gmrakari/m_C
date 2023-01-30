cmake_minimum_required(VERSION 3.1)

project(asynCallBackFun C)

set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE src_dir_list "src/*c")

find_package(Threads)

add_executable(asynCallBackFun ${src_dir_list})

target_link_libraries(asynCallBackFun ${CMAKE_THREAD_LIBS_INIT})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
