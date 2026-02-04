# Better structure for CMake
The project is a very small one. Realistic programs have sometimes hundreds of header and source files.
So whilst it is theoretically possible to create only one CMakeLists.txt file, it would quickly become messy
and unmaintainable.

# Include sub-directories
The best way to structure the `cmake hierarchy` is to follow the `project folder hierarchy`.
Typically only the root-folder and sub-folders containing C++ source files have a CMakeLists.txt,
but this is not a restriction: you can put a CMakeLists.txt anywhere you like.

The way to tell cmake to include sub-directories for processing is the instruction `add_subdirectory`.

00) in the Step03 - root directory create a build sub-folder
01) in the Step03/src folder create a CMakelists.txt file, e.g. by `touch ./src/CMakeLists.txt`
02) edit ./CMakeLists.txt and ./src/CMakeLists.txt and move the line
```
add_executable(step3 src/step3.cc src/greeter.cc)
```
from ./CMakeLists.txt to ./src/CMakeLists.txt and save both files
03) edit the file ./CMakeLists.txt in the root directory and add the line at the end and save.
```
add_subdirectory(src)
```
04) in the build folder run `cmake ..`
05) observe: The build fails with error message
```
CMake Error at src/CMakeLists.txt:1 (add_executable):
  Cannot find source file:

    src/step3.cc
```
06) edit src/CMakeLists.txt to remove `src/` from the add_executable target file
07) save and run cmake again.
08) run `make` and this time the executable will be built successfully

# What's tricks?
cmake looks for files in relative folders to the current folder, so since the CMakeLists.txt
is *in* the folder `./src` we needed to remove the relative path `src` from the files in the add_executable target.

# If you want to try this again then
10) cd CMakeTutorial/Step03
11) rm -rf build
12) cp CMakeLists-backup.txt CMakeLists.txt
13) rm src/CMakeLists.txt


