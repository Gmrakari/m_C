# Add a test for the HTTP library
add_executable(test_http_get test_http_get.c)
target_link_libraries(test_http_get http)

# Add a test for the main program
add_test(NAME test_main COMMAND main)
