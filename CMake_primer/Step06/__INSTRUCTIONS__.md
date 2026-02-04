# Finding and using standard tools and libraries
Almost all C++ projects make use of standard and 3rd party tools and libraries, e.g.
- BOOST template library
- gRPC and protobuf communication generators and libraries
- clang tools/compilers
- ...

Some of these libraries and tools may have been installed via package managers (apt, yum, ..) or
by building them from source (download from github etc).
The normal installation directories are located under `/usr`, but I've also seen installations
under /opt, /home and other non-standard (installation-)directories.
For the compiler to be able to link libraries, the installation paths need to be known, so cmake
provides a set of tools to find and make known the necessary paths.

# Move the greeter-library to a different folder and let cmake find it

00) build the application as before
01) create a folder Step06/installdir
02) *Move* the `libgreeter.a` library from the `Step06/output/lib` folder to the newly created `installdir` folder
```
mv ./output/lib/libgreeter.a ./installdir
```
03) edit the src/CMakeLists.txt file and comment out the line `add_library(greeter STATIC greeter.cc)` by prepending a '#'
    This way we simulate an external pre-built library
04) in the build-folder try to build the application
05) observe: You'll get an error `/usr/bin/ld: cannot find -lgreeter: No such file or directory`

This is because we moved the library out of the known location to the unknown location `installdir`

10) edit the src/CMakeLists.txt file again adding the following lines before the executable target:
```
set(CMAKE_PREFIX_PATH "/usr/lib;/usr/slib;${CMAKE_PREFIX_PATH};${CMAKE_SOURCE_DIR}/installdir")
message("CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
find_library(GREETER_LIB NAMES greeter)
message("GREETER_LIB=${GREETER_LIB}")
```
11) change the line `target_link_libraries(step6 greeter)` to
                    `target_link_libraries(step6 ${GREETER_LIB})`
12) Build again
13) observe: we get two additional (debug) messages informing us about the CMAKE_PREFIX_PATH and 
             the GREETER_LIB
14) observe: the build succeeds

The instruction `set(CMAKE_PREFIX_PATH ...)` sets a PATH variable where to look for libraries.
The `find_library(GREETER_LIB ...)` instruction looks in this path for files described in the NAMES -
part of the instruction. It looks for lib<name>(_<version>)?.(.a|.so) files etc and populates the variable
`GREETER_LIB` with the path of any found file. If no file is found GREETER_LIB will be set to the value:
`GREETER_LIB-NOTFOUND`.

_NOTE_: In all fairness this is a contrived example, as we built the library and are masters of our file-system
        we would not need to call find_library, but instead add the location of the library to our library
        search path with the instruction `link_directories(...)` which actually sets a search path similar to
        the Linux $PATH and $LD_LIBRARY_PATH

# Extra credit
cmake has a facility to download external tools from external repositories like github.
This can be lengthy, as there will be a download, a build and a make-available step.
If you want, you can try to get the googletest libraries by adding the following lines
to your root CMakeLists.txt

```
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(FETCHCONTENT_QUIET OFF)
#For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
```
Each time you build now the repository of googletest will be downloaded, unzipped and built.
Once you are more familiar with scripting in cmake, you could make this conditional on whether
the googletest libraries are already present.


# If you want to try this again then
20) cd CMakeTutorial/Step06
21) rm -rf build output instlldir
22) cp CMakeLists-backup.txt CMakeLists.txt
23) cp src/CMakeLists-backup.txt src/CMakeLists.txt

