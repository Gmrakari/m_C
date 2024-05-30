cmake_minimum_required(VERSION 3.10)
project(cjson_lib C)

file(GLOB cJSON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB cJSON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(cjson ${cJSON_SOURCES} ${cJSON_HEADERS})

target_include_directories(cjson PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS cjson
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${cJSON_HEADERS} DESTINATION include)
