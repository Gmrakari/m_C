cmake_minimum_required(VERSION 3.10)
project(jpeg_lib C)

file(GLOB JPEG_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB JPEG_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(jpeg ${JPEG_SOURCES} ${JPEG_HEADERS})

target_include_directories(jpeg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS jpeg
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${JPEG_HEADERS} DESTINATION include)
