# Conditional builds/build configurations
One of the powerful features of cmake is, that we can define the build process in a way so that it 
can be customised for different conditions.
Say we want to create an application that has the absolutely best performance, when it is run in a
production environment. An application like that would
- strip all debugging- and unnecessary symbol information from the executable
- optimise loops, inline functions, etc
- strip information about source-file-locations 
- and more...

If a such optimised program encountered a bug, and we wanted to debug it, then we better be good with assembler,
because a debugger like gdb would only be of limited help.
So we would probably like to have a second version of the executable that has not been stripped of this information - 
a DEBUG - build. The executable this Debug configuration would be bigger, slower and unsafer, as it would contain
more information about the program, but it would be debuggable.

## Standard configurations
- Debug:            Debug build, most or all optimisations disabled, full symbol-table 
- Release:          Fully ptimised for size and speed 
- RelWithDebInfo:   Partially optimised with some debug-information so that some debugging can be performed
- MinSizeRel:       Release configuration with minimal size requirements

_NOTE_: It is possible to also create non-standard build-types (e.g. `Coverage`, and more). Will not do this here.

00) in the root CMakeLists.txt add the following lines after the `cmake_minimum_required` instruction
```
# set a default build-type
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_BUILD_TYPE
    ${CMAKE_BUILD_TYPE}
    CACHE STRING "Debug Release RelWithDebInfo MinSizeRel")

# selection of possible types
set(CMAKE_CONFIGURATION_TYPES
    "Debug;Release;RelWithDebInfo;MinSizeRel"
    CACHE STRING "Configs" FORCE)

message("CMAKE_BUILD_TYPE=" ${CMAKE_BUILD_TYPE})

# Common C++ flags
set(CMAKE_CXX_FLAGS
    -rdynamic -Wall -Werror
    CACHE STRING "Default C++ compiler flags")

# Flags for Debug build
set(CMAKE_CXX_FLAGS_DEBUG
    "-g"
    CACHE STRING "g++ debug flags")

# Flags for Release with debug info
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
    "-g -O2"
    CACHE STRING "g++ rel+dbg flags")

# Flags for optimised release targets
set(CMAKE_CXX_FLAGS_RELEASE
    "-O2"
    CACHE STRING "g++ release flags")

# this adds a suffix to the name of any created library, if the configuration is "Debug"
set(CMAKE_DEBUG_POSTFIX _dbg)
```
01) In the file src/CMakeLists.txt append the line
```
set_target_properties(step7 PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
```
02) save and go to the build-directory and build with command (`cmake -DCMAKE_BUILD_TYPE=Release .. ; make`)
03) observe: - an extra info message is printed on cmake: `CMAKE_BUILD_TYPE=Release`
               this means now the build is now set to Release
             - the  executables are built as before
04) Now we want to start a Debug build so run the command: `cmake -DCMAKE_BUILD_TYPE=Debug ..`
05) observe: the build-type message has no changed to: `CMAKE_BUILD_TYPE=Debug`
06) run `make`
07) observe: a new compilation/link starts and the library and executable have a "_dbg" suffix
08) change to the executable output directory (`cd ../output/bin`)
09) run: `strings step7 > step7.str ; strings step7_dbg > step7_dbg.str`
    This just creates 2 text files (one for each exe) containing readable strings in the respective executables
10) run: `diff step7.str step7_dbg.str`

_NOTE_: diff is a command-line comparison utility, but you can use the VSCode-comparison for visual comparison
        if you prefer
        
11) compare sizes of debug and release executables and their respective string files: ( `ls -Fasl`)

# Extra credits
If you know gdb, you can try debugging either of the executables in turn.
    

# If you want to try this again then
20) cd CMakeTutorial/Step07
21) rm -rf build output instlldir
22) cp CMakeLists-backup.txt CMakeLists.txt
23) cp src/CMakeLists-backup.txt src/CMakeLists.txt

