add_library(greeter STATIC greeter.cc)
add_executable(step6 step6.cc greeter.cc)
target_link_libraries(step6 greeter)
