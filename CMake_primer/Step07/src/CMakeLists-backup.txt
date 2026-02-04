add_library(greeter STATIC greeter.cc)
add_executable(step7 step7.cc greeter.cc)
target_link_libraries(step7 greeter)
