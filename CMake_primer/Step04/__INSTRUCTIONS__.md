# Add a library and link to it
Almost always in C++ we use libraries to re-use code and increase productivity.
Now we will create a library and link it to the executable.

# Add a library target
Cmake has another target type for libraries similar to `add_executable` called
`add_library`

00) edit src/CMakeLists.txt and add the following lines to the start of the file:
```
add_library(greeter STATIC greeter.cc)
```
01) remove the `greeter.cc` from the step4 executable target:
change
```
add_executable(step4 step4.cc greeter.cc)
```
to
```
add_executable(step4 step4.cc)
```
02) save, create and change into a build directory and try to build
03) observe1: The library builds correctly:
```
[100%] Linking CXX static library libgreeter.a
[100%] Built target greeter
```
04) observe2: The build of the executable fails with the familiar error `undefined reference to 'sayHello()'`

The reason for this is that we did not tell cmake that the greeter library is necessary for the build of the executable `step4`.
So we need to tell cmake that the executable target `step4` needs a library called `greeter`.

_NOTE_: In Posix systems library-filneames typically follow the naming convention `lib<name>(_)?<version>[<debug-tag>]?.(a|so)`,
        for example `libdietersutils_1.0.2.a`.
        In cmake it is sufficient to provide the <name> - part of the filename (here: `dietersutils`) to identify the library.
        In our case we created the library file `libgreeter.a` which we want to link to the exe.

10) add the following line at the end of the file src/CMakeLists.txt
```
target_link_libraries(step4 greeter)
```
This tells cmake that the target (-executable) `step4` needs to be linked to library `libgreeter.a`

11) run `make` again
12) observe that the build is now successful (find both the library and the executable in the build/src folder)

# If you want to try this again then
20) cd CMakeTutorial/Step04
21) rm -rf build
22) cp CMakeLists-backup.txt CMakeLists.txt
23) cp src/CMakeLists-backup.txt src/CMakeLists.txt
