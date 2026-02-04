# Construction/Destruction

Creating dynamic vectors requires careful memory management. C++ provides `new`/`delete` (not `malloc`/`free`).

**`new` allocates memory and calls constructors** (bottom-up for inheritance):
- Allocate: `sizeof(BaseA) + sizeof(BaseB) + sizeof(Child)`
- Call: `BaseA()`, `BaseB()`, `Child()`

**`delete` calls destructors and frees memory** (top-down for inheritance):
- Call: `~Child()`, `~BaseB()`, `~BaseA()`
- Free memory

## Pointers: The Core Problem

A pointer is just an integer (memory address). The compiler can't track ownership:
- **Multiple pointers → same address**: Which should call `delete`?
- **Offset pointers**: Should never be deleted
- **Uninitialized pointers**: Deleting causes undefined behavior

**Ownership must be explicit.**

## RAII: Allocate in Constructor, Deallocate in Destructor

The naive implementation crashes. You'll see why...

## Task 1: Run the Program
```bash
cmake . && cmake --build . && ./output/bin/add_vectors
```

Seems to work? Uncomment `#define TASK1` in `add_vectors.cc` and rebuild.

What breaks? Why?

## Auto-Generated Methods

C++ silently generates these:
- **Default Constructor**: Called if no other constructor exists
- **Copy Constructor**: Shallow copy by default
- **Assignment Operator**: Shallow copy by default
- **Destructor**: Called on object destruction

*These shallow copies cause the crash.*

## Task 2: Trace Calls

Uncomment `#define TASK2` to see method calls.

**Observation**: Two objects delete the same pointer (double-delete error). This is because the auto-generated copy constructor made a shallow copy.

## Task 3: Implement Copy Operations

Uncomment `#define TASK3` in `vector_nd_ptr.h` and `.cc`.

**Observation**: Copy constructor and assignment operator are invoked. The defaults do shallow copies; we need deep copies.

## Task 4: The Root Cause

**The Problem**: Default copy copies pointers (integers) by value. Both objects end up pointing to the same heap memory.

**The Result**: First `delete[]` succeeds; second causes undefined behavior.

**The Solution**: Implement deep-copy semantics in the copy constructor and assignment operator.
Uncomment:
```C++
#define TASK4
```
Re-build and run.

Observe:
- pay attention to the memeory addresses of the objects and their `pVec_` members.
- the program now works and does no longer crash

If you want to get rid of the debug-comments, then uncomment:
```C++
#define TASK2
```
Re-build and run.
