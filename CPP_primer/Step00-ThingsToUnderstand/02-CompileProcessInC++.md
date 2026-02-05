
# C++ Compilation Process

The diagram below shows the main stages a C++ source file goes through to become an executable.

```mermaid
%%{init: {'themeVariables': { 'fontSize': '18px', 'nodePadding': 16 }}}%%
flowchart TD
  A["Source files (.cpp, .cc)"] --> B["Preprocessing (include headers, expand macros)"]
  B --> C["Compilation (parsing, semantic analysis, codegen)"]
  C --> D["Assembly / IR generation (intermediate representation)"]
  D --> E["Assembly"]
  E --> F["Object files (.o, .obj)"]
  F --> G["Linking"]
  G --> H["Executable / Shared Object (.out, .exe, .so, .dll)"]
  H --> I["Loader / Runtime (program loaded into memory and started)"]

  subgraph Tools
    T1["g++ / clang++"]
    T2["as (assembler)"]
    T3["ld / linker"]
  end

  C -->|invoked by| T1
  D -->|invoked by| T2
  F -->|invoked by| T3

  classDef bigFont font-size:18px;
  class A,B,C,D,E,F,G,H,I bigFont;

  style A fill:#f9f,stroke:#333,stroke-width:1px
  style G fill:#dfd,stroke:#333,stroke-width:1px
```

Notes:

- Preprocessing produces a translation unit (source with headers expanded).
- The compilation stage performs parsing, semantic analysis, and code generation (often producing assembly or IR).
- Assembly turns assembly/IR into object files.
- The linker combines object files and libraries (static or dynamic) to produce the final executable or shared object.
- The loader/runtime loads the executable into memory and performs dynamic linking if needed.

