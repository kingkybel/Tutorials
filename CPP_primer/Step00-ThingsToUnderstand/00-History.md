# Genesis of C++

---
**In the beginning, Man created assembler.**

**And in the image of machines created He him.**

---

- **Bit:** single unit of binary information
- **Byte:** 8 bits (standard modern unit)
- Memory hierarchy: terabytes (storage), gigabytes (RAM), megabytes (cache), kilobytes (PROM)
- Smaller memory = faster access

## Early Computers & Assembly

A fundamental property: **programs and data share the same memory**. (Viruses exploit this.)

Early programmers wrote assembly—manipulating registers and memory directly:
- Flow control via label jumps
- Hardware-specific instruction sets
- Slow to write, hard to debug, difficult to maintain
- Repetitive code

A Fibonacci in assembly needs 30+ lines of register manipulation for simple logic.

- Assembly is manipulating registers and memory addresses.
- Flow control via jumps
- Slow, hard to debug, unmaintainable

## Solution: C

C was invented to solve this. It provides **human-friendly abstractions:**
- Named **variables** instead of raw registers
- Named **functions** for repeated instruction sequences
- Syntactic sugar for data access/referencing

The algorithm is clear, types are explicit, control flow is obvious—no memory address manipulation needed.

**Trade-off:** C requires compilation and still demands understanding the underlying machine architecture.

## Problems with C

As programs grew larger and more complex:
- Manual memory allocation/deallocation
- Long, cluttered naming and parameter lists
- Syntactical hassles leading to unreadable code

**Need:** Better abstractions and organization

## C++

C++ was first released **1985** as an extension to C. It was standardized in **1998** as C++98.

**Key additions:**
- Classes (object-oriented programming)
- Templates (generic programming)
- STL standard library (containers, algorithms)
- Namespaces (organization)
- Function/operator overloading (cleaner names)
