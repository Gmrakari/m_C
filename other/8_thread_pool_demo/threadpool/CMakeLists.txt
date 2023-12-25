add_library(threadpool src/threadpool.c)

target_include_directories(threadpool
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)