cmake_minimum_required(VERSION 3.8)

project(
  Step3
  VERSION 1.0
  LANGUAGES CXX)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  )

add_subdirectory(src)