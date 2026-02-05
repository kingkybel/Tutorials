# Short introduction into C++

## Prerequisites
- computer with Linux/WSL
- installed G++ and cmake
```bash
sudo apt update
sudo apt install build-essential
sudo apt install g++-14
sudo apt install cmake
```
- installed `tree`
```bash
sudo apt install tree
```
- VSCode or similar, Also good to have `mermaid` renderer for graphs

## Why C++
C++ dominates where performance is critical:
- **High-performance computing**: trading, gaming, AI engines, robotics
- **Resource-constrained systems**: embedded systems, drones, satellites
- **Legacy code**: too expensive to replace

## Why C++ Works
- Bare-metal execution (no VM overhead)
- Machine-level optimization
- Minimal compiled code size with readable syntax
- Per-hardware optimization
- Compile-time metaprogramming
- "Pay only for what you use" philosophy

## What we cover

- History, memory model, compilation: [Step00-ThingsToUnderstand](Step00-ThingsToUnderstand)
- How to build executables using `cmake`: [Step01-HelloWorld](Step01-HelloWorld)
- C++ = C + objects ??! : [Step02-Objects](Step02-Objects)
- The biggest trap for beginners --> auto-generated methods: [Step03-ConstructDestruct](Step03-ConstructDestruct)
- First look at STL-containers: [Step04-AvoidingPointers](Step04-AvoidingPointers)

