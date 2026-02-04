# Modifying where to put artefacts
A bit annoying is, that the executables and libraries are put into the bowels of the build directory.
It can be difficult to find the artefacts, which, after all, are what we do the build for in the first place.

# Adjusting CMAKE_* variables
cmake provides a lot of variables to customize builds. They include:
- directories
- tools
- (compile-) parameters
- and more ...

They start with `CMAKE_` so you should avoid using this prefix for your custom-variables, lest you inadvertently
override any existing one.
For writing output of your build to a custom location cmake provides the following variables:

- `CMAKE_RUNTIME_OUTPUT_DIRECTORY`: location for executables
- `CMAKE_LIBRARY_OUTPUT_DIRECTORY`: location for dynamic libraries (*.so, *.dll)
- `CMAKE_ARCHIVE_OUTPUT_DIRECTORY`: location for static libraries (*.a, *.lib)

00) in the root CMakeLists.txt add the following lines
```
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)
```
01) run cmake in your build directory
02) observe: the folders Step05/output/bin and Step05/output/lib are created
04) run `make`
05) observe:
    - the libgreeter.a file is in the `Step05/output/lib` folder
    - the step5 executable is in the `Step05/output/bin` folder

# Extra credits
Create a dynamic (SHARED) library instead of a static one and see where the resulting *.so file is put

# If you want to try this again then
10) cd CMakeTutorial/Step05
11) rm -rf build output
12) cp CMakeLists-backup.txt CMakeLists.txt
13) cp src/CMakeLists-backup.txt src/CMakeLists.txt
