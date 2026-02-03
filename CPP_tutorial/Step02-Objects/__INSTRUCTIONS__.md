# Objects in C++

## Overview
Objects combine data with operations. C++ supports OOP but doesn't require it (unlike Java).

**`class` vs `struct`**: Only difference is default visibility:
- `struct`: members are `public` by default
- `class`: members are `private` by default
- Both support `protected` for derived classes

## Key Concepts
- **Declaration**: Headers; **Implementation**: separate `.cc` files
- **Member functions**: Can be declared and implemented in separate files
- **Special methods**: Constructors, operators (e.g., `+` for Vector3D)
- **Defaults**: Member variables and function parameters support default values
- **Copy semantics**: Objects are copies, not references
- **Const correctness**: Helps compiler and developer prevent mutations

