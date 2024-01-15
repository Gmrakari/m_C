add_library(cli_cmd_lib src/cmd_base.c src/cmd_core.c)

target_include_directories(cli_cmd_lib
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)