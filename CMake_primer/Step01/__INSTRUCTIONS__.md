
# Explore the directory
00) in VSCode open a new terminal by clicking `Terminal->New Terminal`
01) in the commandline terminal change to the Step01 directory (`cd Step01`)
02) run: `ls -Fax`
03) observe: only a step1.cc (C++ source) is present (apart from these instructions)

# Use "make" to build an executable
In Posix systems where make is installed, simple compile operations can be done without any Makefiles
10) type: `make step1`
11) observe: a compilation is performed and an executable file "step1" is created.
12) type `./step1` to execute the file to verify a hello world message is printed

## Why does this work?
    - only system headers and system libraries are used for this simple project
    - system headers and system libraries are in standard directories - as per default installation
    - make is installed
    - make knows what to do with simple *.cpp, *.cc files

# Use cmake to build the executable
The build of the executable worked fine, so why bother with cmake?
    - you might want to use libraries/headers that are not in the standard path or are non-standard themthelves
    - your executable consists of more than one file
    - you want different versions of the build (debug/release/performance test/...)
    -...
Solution is to define what steps to take to create the executable in one or more `CMakeLists.txt` files.
The CMakeLists.txt is a fixed name (case sensitive) and we will create it as simple as it gets.

20) in VSCode create a file called `CMakeLists.txt`
21) Add the following lines to the file and save:
```
cmake_minimum_required(VERSION 3.8)
project(Step1 LANGUAGES CXX)
add_executable(step1 step1.cc)
```
22) open the file step1.cc and verify it is a syntacially correct C++ main file of a hello-world program (or take my word for it)
_NOTE_: - `cmake_minimum_required`, `project` and `add_executable`(step1 step1.cc) are the only instructions in the file
        - "#" lines are comments
23) go back to the terminal and make sure you're in the Step01 directory
23) run: `cmake .`
24) run: `ls -Fax`
25) observe: files and folders are created, but no `step1` executable
26) run: `make`
27) run: `ls -Fax`
28) observe: executable ./step1 is created
29) run: `./step1`
30) observe: "Hello World"

# Housekeeping
The above works, but "clutters" the directory with cmake intermediate files.
To avoid that, create a build directory and build from there:

40) `rm -rf CMakeCache.txt CMakeFiles/ cmake_install.cmake Makefile step1`
41) `mkdir ./build`
42) `cd build`
43) `cmake ..`
_NOTE_: This command now uses the parent-directory `..`
44) `make`
45) observe: files and folders created and executable built in build folder and not cluttering project directory
_NOTE_: The build directory is a file that is intended as working directory - subject to being removed - and should not be
        used for project-files that you want to keep.
    
# If you want to try this again then
50) rm -rf build/ CMakeLists.txt

