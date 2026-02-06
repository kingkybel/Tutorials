# Tutorials/primers
This is a collection of tutorials, primers and cheat-sheets that I shared with colleagues and team-members over the years.

## Prerequisites
All the tutorials here were developed on (Ubuntu) Linux and are not tested on any other operating system.
Most of the tutorials should however work with little or no modification on any Posix-system provided you have a
access to

- `bash` for command-line interactions
- `g++` gnu-C++-compiler. Any other compile should be able to compile the given sources, but modifications might be
        necessary in cmake-files
- `cmake` for building executables
- `git` for version control
- an IDE like `VSCode` or `CLion`
- `mermaid` - plugin to view schematic graphs

## Tutorials & Primers

### [Bash Primer](Bash_primer/LinuxCheatSheet.md)
Command-line essentials for Linux/Unix. Learn bash shell commands, scripting, and productivity tips to work efficiently on the command line.

### [Git Cheat Sheet](Git_cheats/Git_cheats.md)
Essential Git commands and workflows for version control. Includes practical examples using the Tutorials repository—branching, committing, merging, and resolving conflicts.

### [CMake Primer](CMake_primer/README.md)
Master CMake, the cross-platform build system for modern C++. Covers the 4-phase compilation process, project configuration, and dependency management through 7 step-by-step examples.

### [C++ Primer](CPP_primer/README.md)
Introduction to C++ with practical examples. Topics include memory management, objects, constructors/destructors, and avoiding pointers. Ideal for developers transitioning from other languages.

### [C++ Templates & Compile-Time Polymorphism](HashDefVsCPP/README.md)
Deep dive into C++ templates for type-safe generic programming. Explores function templates, class templates, specialization, SFINAE, and techniques for zero-runtime-cost abstractions.

### [Template Demo](templateDemo/README.md)
Progressive C++ template tutorial building a `limited_int` template class. Demonstrates how to evolve a simple idea into a robust, feature-rich template through 7 incremental steps with hands-on examples.
