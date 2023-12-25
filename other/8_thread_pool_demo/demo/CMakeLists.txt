add_library(demo src/demo.c) 

target_include_directories(demo
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)