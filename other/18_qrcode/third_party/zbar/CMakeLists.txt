cmake_minimum_required(VERSION 3.10)
project(zbar_lib C)

# file(GLOB ZBAR_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB ZBAR_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# add_library(zbar ${JPEG_SOURCES} ${JPEG_HEADERS})

target_include_directories(zbar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS zbar
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${ZBAR_HEADERS} DESTINATION include)
