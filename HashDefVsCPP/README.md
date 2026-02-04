# C++ Templates - Compile-Time Polymorphism for Performance

## Overview
C++ templates enable compile-time polymorphism, allowing you to write generic code that adapts to different types without runtime overhead.

## Key Benefits
- **Zero runtime cost** - all specialization happens at compile time
- **Type safety** - compile errors catch type mismatches early
- **Performance** - no virtual function calls or dynamic dispatch overhead

## Topics Covered
- Function templates
- Class templates
- Template specialization
- SFINAE and concepts
- Common pitfalls and best practices

## History
C++ is a natural evolution of C, a language specifically developed for high-performance and closeness to the hardware.
C uses many abstract techniques to make programming close to the machine easier for the programmer.
Specifically hash-defines (#define) are used to avoid writing repetitive code without the penalty that is imposed by other C-constructs.

## Build the executables
There is a small bash-script provided to compile the two source code files of this tutorial.
It will generate the respective executables and also the pre-processor output.

Run:
```bash
./make_all
```

You can execute each executable with:
```bash
./step01/hashDef
./step02/templates
```

To review the pre-processor outputs:
```bash
less ./step01/hashDef.prep
less ./step02/templates.prep
```

