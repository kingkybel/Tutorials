# Pre-processor instructions

## What are pre-processor instructions?
| Instruction                | What does it do?      | Example                                                                      |
|----------------------------|-----------------------|------------------------------------------------------------------------------|
| #define                    | define a value/macro  | #define PI 3.1415<br/>#define SQUARE(x) ((x)*(x))                            |
| #if, #ifdef, #else, #endif | conditional inclusion | #ifdef DEBUG<br/>&nbsp;&nbsp;&nbsp;printf("%s", \_\_FUNCTION\_\_);<br/>#endif|
| #pragma                    | compiler-specific     | #pragma once                                                                 |
| #error                     | cause an error ap pre-processor stage | #ifdef WIN32<br/>&nbsp;&nbsp;&nbsp;#error "cannot compile on Windows"<br/>#endif|
| #include                   | include a file into this file | #include "my_header.h"                                               |

Pre-processor instructions are executed at the pre-processing stage of the C/C++ compiler. The main task of the preprocessor is (conditional) textual replacement of defined tokens in the program text.

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

## Investigate the C++ - code
At the top of the file a class called `MultiplicativeType` is defined. This class is needed to dempnstrate that
user-defined tipes can be used in macros. It is called `MultiplicativeType` because it defines the mutiplication 
operator `*`, which is what we need when we want to use a term like `x * y` in our code.
The class also has a streaming operator to make it ease to output to console.

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
of the code in the original `hashDef.cc` file. open the file and scroll to the indicated line:
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
Examine the output - it shows thows a line-number and a function-name for each printed line. Pay attention to:
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
In line 101 we calulate PI + 1 which is 4.1415926. In the following line we calculate the SQUARE with the macro which is indeed
 `17.1527896785340204`. In line 103 we attempt to do the calculation and print it out directly and we get the result `7.2831853000000004`, which
is obviously incorrect.

So what happened?

Reopen the hashDef.prep again and search for `d_pi_plus1`. The following 2 lines give a clue what went wrong:
```C++
    auto d_pi_plus1 = 3.14159265 + 1.0;
    { cout << 102 << " (" << __FUNCTION__ << "): " << "SQUARE(d_pi_plus1)" << "=" << std::fixed << std::setprecision(16) << d_pi_plus1 *d_pi_plus1 << endl; };
    { cout << 103 << " (" << __FUNCTION__ << "): " << "SQUARE(d_pi + 1.0)" << "=" << std::fixed << std::setprecision(16) << d_pi + 1.0 * d_pi + 1.0 << endl; };
```
The second line prints: `d_pi + 1.0 * d_pi + 1.0`, and there is the problem. The macro resolution of macro `SQUARE(x) x * x`. We are calling the
macro with the formal parameter `x` set to `d_pi + 1`. The macro-resolution mechanism replaced every occurence of `x` with `d_pi + 1` resulting
in `d_pi + 1 * d_pi + 1`. Since the compiler evaluates `*` before `+` we get the result `2 d_py + 1`, which is the value we are seeing in line 103.

## Conclusion
Hash-defines can be a convenient way to save the programmer from entering repetitive code, but there are some problems and they can be a source
of subtle bugs.