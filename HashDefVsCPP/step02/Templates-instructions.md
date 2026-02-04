# C++ Templates Instructions

## Overview
C++ templates enable generic programming by allowing you to write code that works with multiple data types. Unlike pre-processor macros (`#define`), templates are **type-aware** and processed by the C++ compiler, providing type safety, better error messages, and avoiding subtle bugs.

## Key Concepts

### Function Templates
Define a single function that works with different types:
```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}
```

### Class Templates
Create generic classes for type flexibility:
```cpp
template <typename T>
class Stack {
private:
    std::vector<T> elements;
public:
    void push(T value);
    T pop();
};
```

### Template Parameters
- `typename T` - Type parameter
- `int N` - Non-type parameter (constants)
- `template <typename> class C` - Template template parameter - DON'T use them!

## Templates vs. Pre-processor Macros: Why Templates Are Superior

### The Problem with `#define` Macros

Pre-processor macros perform **textual replacement** before compilation. This causes several critical issues:

#### 1. **Operator Precedence Bugs**
```cpp
#define SQUARE(x) x * x

double d = 4.14;
auto result1 = SQUARE(d + 1);      // BUG! Expands to: d + 1 * d + 1
                                    // Evaluates as: d + (1*d) + 1, NOT (d+1)*(d+1)
auto result2 = SQUARE(d);           // Works correctly: d * d
```

When you call `SQUARE(d + 1)`, the macro blindly substitutes `x` with `d + 1`, resulting in:
```cpp
d + 1 * d + 1  // Wrong! Operator precedence evaluates * before +
```

With templates, this is not a problem:
```cpp
template <typename T>
T square(T x) {
    return x * x;
}

auto result = square(d + 1);  // Correct! Parentheses are implicit in function semantics
```

#### 2. **No Type Safety**
Macros work on any text, potentially causing nonsensical code:
```cpp
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int result = MAX(++counter, 5);  // BUG! counter is incremented twice!
```

Templates enforce type checking at compile time:
```cpp
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

int result = maximum(++counter, 5);  // Safe: counter incremented once
```

#### 3. **Poor Debugging and Error Messages**
- Macro errors appear as cryptic compiler errors in the *expanded* code, not the macro definition
- Stepping through code with debuggers shows the expanded text, not the original macro
- No visibility into what the macro actually did

Templates produce clear compiler errors that point to the actual problem:
```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

add("hello", 5);  // Clear error: cannot add string and int
```

#### 4. **No Scoping**
Macros pollute the global namespace and can conflict:
```cpp
#define PI 3.14159

// Later in another file...
#define PI 3.14  // Oops! Silently redefines PI everywhere

template <typename T>
constexpr T pi_v = 3.14159265358979323846;  // Better! Scoped, type-specific
```

### The Modern C++ Solution: Templates + `constexpr`

Combine templates with `constexpr` for compile-time computation without macro problems:

```cpp
template <typename T>
constexpr T square(T x) {
    return x * x;
}

constexpr double d = 4.14;
constexpr auto result = square(d);  // Computed at compile-time!

// No runtime overhead, type-safe, debuggable
```

#### Comparison Table

| Feature | `#define` Macro | Template | `constexpr` |
|---------|-----------------|----------|------------|
| Type Safety | ❌ No | ✅ Yes | ✅ Yes |
| Operator Precedence Safe | ❌ No (requires extra parentheses) | ✅ Yes | ✅ Yes |
| Compiler Type Checking | ❌ No | ✅ Yes | ✅ Yes |
| Clear Error Messages | ❌ No | ✅ Yes | ✅ Yes |
| Debuggable | ❌ No | ✅ Yes | ✅ Yes |
| Scoped/Namespaced | ❌ No | ✅ Yes | ✅ Yes |
| Compile-time Evaluation | ⚠️ Limited | ⚠️ Limited | ✅ Yes |
| No Side Effects | ❌ Prone to bugs | ✅ Yes | ✅ Yes |

## Best Practices
- **Prefer templates over macros** for generic code
- **Use `constexpr` functions** for compile-time constants instead of `#define`
- Keep template implementations in **header files**
- Use meaningful template parameter names
- Provide template specializations when needed
- Always parenthesize macro parameters (but better: don't use macros!)

## When to Use What

- **`#define`**: Only for platform-specific code or compiler directives (e.g., `#pragma once`, `#ifdef DEBUG`)
- **Templates**: Generic algorithms and data structures where you need type flexibility
- **`constexpr`**: Compile-time constants and functions that can be evaluated at compile-time
