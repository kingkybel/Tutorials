add_library(greeter STATIC greeter.cc)
add_executable(step5 step5.cc greeter.cc)
target_link_libraries(step5 greeter)
