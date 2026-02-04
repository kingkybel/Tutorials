cmake_minimum_required(VERSION 3.8)

project(
  Step3
  VERSION 1.0
  LANGUAGES CXX)

add_executable(step3 src/step3.cc src/greeter.cc)
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  )

