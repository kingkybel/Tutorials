# Building a Simple Hello World Program

## Examine the Code
View the directory structure:
```bash
tree Step01-HelloWorld
```
```bash
Step01-HelloWorld/
├── CMakeLists.txt
├── include
│   └── greeter.h
├── __INSTRUCTIONS__.md
└── src
    ├── CMakeLists.txt
    ├── greeter.cc
    └── hello_world.cc
```
Examine the contents.

### Key Observations:
- C++ looks like C (mostly backward compatible)
- Headers (`.h`) declare, sources (`.cc`) implement
- Entry point: `main()` in `hello_world.cc`
- `CMakeLists.txt`: declarative build system (what, not how)

## Build

Create build instructions (requires path to root CMakeLists.txt):
```bash
cd Step01-HelloWorld
cmake .
```
### Observe
CMake generates configuration files:
```bash
.
├── CMakeCache.txt
├── CMakeFiles/
├── Makefile
├── output/
│   └── bin/              # Target for executable
└── src/
```

Build the executable:
```bash
cmake --build .
```

- Executable created at `./output/bin/hello_world`

## Better: Out-of-Source Build
Keep generated files separate from sources:
```bash
rm -rf CMakeCache.txt CMakeFiles/ cmake_install.cmake Makefile output/ src/CMakeFiles/ src/cmake_install.cmake src/Makefile
mkdir build
cd build
cmake ..
cmake --build .
```

Result: All generated files in `build/` directory. Executable at `output/bin/hello_world`.
