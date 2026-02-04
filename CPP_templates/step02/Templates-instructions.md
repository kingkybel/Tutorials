# C++ Templates Instructions

## Overview
C++ templates enable generic programming by allowing you to write code that works with multiple data types.

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

## Best Practices
- Keep template implementations in header files
- Use meaningful template parameter names
- Provide template specializations when needed
