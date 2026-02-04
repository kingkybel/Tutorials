# Pre-processor instructions

## What are Pre-processor Instructions?

Pre-processor instructions are directives processed by the C++ pre-processor **before compilation**. They perform textual manipulation on your source code. The pre-processor is a text processor that runs **before the C++ compiler**. Its primary job is to perform textual replacement: it finds defined tokens in your source code and replaces them with their definitions. This happens before the compiler even sees your code.

| Instruction | Purpose | Example |
|---|---|---|
| `#define` | Define a constant or macro for textual substitution | `#define PI 3.1415`<br/>`#define SQUARE(x) ((x)*(x))` |
| `#ifdef`, `#else`, `#endif` | Conditional compilation based on whether a macro is defined | `#ifdef DEBUG`<br/>`  std::cout << "Debug mode" << std::endl;`<br/>`#endif` |
| `#if`, `#elif` | Conditional compilation based on constant expressions | `#if __cplusplus >= 201703L`<br/>`  // C++17 or later`<br/>`#endif` |
| `#include` | Include file contents at this location | `#include <iostream>`<br/>`#include "myheader.h"` |
| `#pragma` | Compiler-specific directives | `#pragma once` (include guard) |
| `#error` | Generate a compile-time error | `#ifdef WIN32`<br/>`  #error "Windows not supported"`<br/>`#endif` |

## Can I see what the pre-processor has done to my code?

Absolutely! 

Run the pre-compile only, e.g. with the GNU-C++-compiler:
```bash
g++ -E ./myCppSource.cc -o myCppSource.prep
```
The output-file `myCppSource.prep` is a readable text-file based on your source `myCppSource.cc` with all include files added and all macros applied.

After you run the above command you can view the file `myCppSource.prep` with the viewer/editor of your choice.

If you have not done so yet, run:
```bash
../make_all
```
from this directory and view the file `hashDef.prep`. Try to find strings `SQUARE`, `OUT`, `PI` (use whole-word and case-sensitive search!).

You will only find `SQUARE` inside of strings, but no sign of `PI` or `OUT`. Instead you will find instances where
the tokens have been replaced with the evaluated macro.

## Investigate the C++ Code

At the top of `hashDef.cc`, a class called `MultiplicativeType` is defined. This class demonstrates that
user-defined types can be used in macros. It's named `MultiplicativeType` because it overloads the multiplication
operator `*`, which is necessary for the `SQUARE` macro to work on custom types.
The class also implements an output stream operator (`operator<<`) for easy console output.

After that there are a number of hash-defines/macro definitions.

```C++
#define SQUARE(value) value * value

#define OUT(var)                                                                    \
    {                                                                               \
        cout << __LINE__ << " (" << __FUNCTION__ << "): "                           \
              << #var << "=" << std::fixed << std::setprecision(16) << var << endl; \
    }

#define PI 3.14159265

#define FUNCTION1(ret_type, name, par_type, parameter)                                                                \
    ret_type name(par_type parameter)                                                                                 \
    {                                                                                                                 \
        cout << "Entering " << #ret_type << " " << #name << "(" << #par_type << " " << #parameter << "(" << parameter \
             << ")"                                                                                                   \
             << ")" << endl;

#define END_FUNCTION1          \
    cout << "exiting" << endl; \
    }

FUNCTION1(void, myFunc, int, i)
int loc_i = 47;
cout << i << "," << loc_i << endl;
END_FUNCTION1

#define COMPLEX_CLASS(value_type)                                                           \
    struct Complex_##value_type                                                             \
    {                                                                                       \
        value_type      real;                                                               \
        value_type      imag;                                                               \
        friend ostream &operator<<(ostream &os, const Complex_##value_type &cplx)           \
        {                                                                                   \
            os << "Complex_" << #value_type << "[" << cplx.real << "," << cplx.imag << "]"; \
            return os;                                                                      \
        }                                                                                   \
    };

COMPLEX_CLASS(double);

COMPLEX_CLASS(int);

COMPLEX_CLASS(MultiplicativeType);
```

Open the file `hashDef.prep` again and search for the string `myFunc`. You will see something similar to:
```C++
# 60 "./hashDef.cc"
void myFunc(int i) { cout << "Entering " << "void" << " " << "myFunc" << "(" << "int" << " " << "i" << "(" << i << ")" << ")" << endl;
int loc_i = 47;
cout << i << "," << loc_i << endl;
cout << "exiting" << endl; }
# 77 "./hashDef.cc"
```
This is a perfectly valid piece of C++. The `# 60 "./hashDef.cc"` and `# 77 "./hashDef.cc"` in this snippet point to the start and end locations
of the code in the original `hashDef.cc` file. Open the file and scroll to the indicated line:
```C++
FUNCTION1(void, myFunc, int, i)
int loc_i = 47;
cout << i << "," << loc_i << endl;
END_FUNCTION1
```
The pre-processor has replaced
```C++
FUNCTION1(void, myFunc, int, i)
```
 with
```C++
void myFunc(int i) { cout << "Entering " << "void" << " " << "myFunc" << "(" << "int" << " " << "i" << "(" << i << ")" << ")" << endl;
```
and
```C++
END_FUNCTION1
```
with 
```C++
cout << "exiting" << endl; }
```

At the bottom of the `hashDef.cc` you can find the classes `Complex_double`. `Complex_int`, and `Complex_MultiplicativeType`. Try to find their
declaration and definition in the *.cc file. Where are they?

Now open the `hashDef.prep` and try to find them. 

## Run the program
So far you might say "Well, that is not so bad, right?!". There is a bug in the code that actually nicely shows limitations of hash-defines.

Run the program:
```bash
./step01/hashDef
```
Examine the output—it displays the line number and function name for each printed line. Pay attention to:
```bash
102 (main): SQUARE(d_pi_plus1)=17.1527896785340204
103 (main): SQUARE(d_pi + 1.0)=7.2831853000000004
```
And then examine the corresponding lines in the code:
```C++
    // Strange behaviour below
    auto d_pi_plus1 = PI + 1.0; // line 101
    OUT(SQUARE(d_pi_plus1));    // line 102
    OUT(SQUARE(d_pi + 1.0));    // line 103
```
In line 101, we calculate `PI + 1` which equals approximately `4.1415926`. In line 102, we use the `SQUARE` macro on this variable, correctly getting
`17.1527896785340204` (≈ 4.14²). In line 103, we call `SQUARE` directly on the expression `PI + 1.0`, but we get the wrong result: `7.2831853000000004`, which
is clearly incorrect.

**So what went wrong?**

Reopen `hashDef.prep` and search for `d_pi_plus1`. The following 2 lines reveal the problem:
```C++
    auto d_pi_plus1 = 3.14159265 + 1.0;
    { cout << 102 << " (" << __FUNCTION__ << "): " << "SQUARE(d_pi_plus1)" << "=" << std::fixed << std::setprecision(16) << d_pi_plus1 * d_pi_plus1 << endl; };
    { cout << 103 << " (" << __FUNCTION__ << "): " << "SQUARE(d_pi + 1.0)" << "=" << std::fixed << std::setprecision(16) << d_pi + 1.0 * d_pi + 1.0 << endl; };
```
The problem is in the second line: it expands to `d_pi + 1.0 * d_pi + 1.0` instead of `(d_pi + 1.0) * (d_pi + 1.0)`.

**What happened during macro expansion:**
- The macro `SQUARE(x)` is defined as `x * x` (note: no parentheses around `x`!)
- When we call `SQUARE(d_pi + 1.0)`, the pre-processor substitutes `x` with `d_pi + 1.0` everywhere
- Result: `d_pi + 1.0 * d_pi + 1.0`
- The C++ compiler evaluates `*` before `+` (operator precedence), so this becomes: `d_pi + (1.0 * d_pi) + 1.0`
- Which equals: `(2 * d_pi) + 1.0` ≈ `7.283...` (the wrong answer!)

## Conclusion: The Dangers of `#define` Macros

While `#define` macros may seem convenient for avoiding repetitive code, they have serious limitations:

1. **No type safety** - Macros work on raw text, not types
2. **Operator precedence issues** - Missing parentheses lead to subtle, hard-to-find bugs (as demonstrated above)
3. **Poor debugging** - Errors occur in the *expanded* code, not the macro definition
4. **Namespace pollution** - Macros are global and can silently redefine earlier definitions
5. **No scope** - Can't be contained within classes or namespaces

**Modern C++ alternatives:** Use templates and `constexpr` functions instead. They provide the same compile-time benefits without these pitfalls. See `Templates-instructions.md` for details.