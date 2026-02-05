cmake_minimum_required(VERSION 3.10)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(
  Step02-Objects
  VERSION 1.0
  LANGUAGES CXX)

# define where artefacts should be put upon successful compilation
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)

# additional include-directories for your project
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  )

# sub-directories where other CMakeLists.txt files are located
add_subdirectory(src)
