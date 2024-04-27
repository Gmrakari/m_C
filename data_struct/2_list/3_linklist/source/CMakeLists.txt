cmake_minimum_required(VERSION 3.0)

project(linklistlib C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB LIB_SRCS "src/*c")

add_library(linklistlib ${LIB_SRCS})

target_compile_options(linklistlib PRIVATE -fPIC)