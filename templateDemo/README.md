# templateDemo: Limited Integer Template Tutorial

## Overview

`templateDemo` is an educational C++ template project that demonstrates the progressive development of a `limited_int` template class. This template constrains integer values to a specified range and automatically handles out-of-bounds values through configurable policies.

The project shows how to evolve a simple idea into a robust, feature-rich template by progressively addressing issues and improving the design through 7 steps (0-6).

## Building and Running

### Build the Project

```bash
cd templateDemo/build
cmake --build .
```

### Run a Specific Step

By default, the build runs **Step 0**. To run a different step, edit `src/main.cc` and change the `STEP` macro:

```cpp
#define STEP 0   // Change this to 0, 1, 2, 3, 4, 5, or 6
```

Then rebuild:

```bash
cmake --build .
../output/bin/demo
```

## The Steps: Progressive Evolution

### Step 0: Plain Integers (The Problem)

**File:** `include/limited_int_0.h`

**What:** Uses plain `int32_t` with no constraints. Demonstrates the problem of uncontrolled values.

**Problem:**
- No range enforcement
- Values like `510` assigned to a Deg360 (0-359) type go unchecked
- Manual modulo operations needed
- Type safety is completely missing
- No way to prevent assignments between incompatible ranges

**Example:**
```cpp
int32_t deg360 = 510;  // Oops! Out of range but silently accepted
```

---

### Step 1: Basic Template with Modulo

**File:** `include/limited_int_1.h`

**What:** Introduces the `limited_int` template that automatically constrains values using modulo arithmetic.

**Improvements:**
- ✅ Automatic range enforcement via modulo operation
- ✅ Template-based type safety
- ✅ Static type definitions: `Deg360`, `Deg180`, `Rad2Pi`
- ✅ Helper method `describe_me()` to show template configuration

**Design:**
```cpp
template<typename T_, T_ min_ = ..., T_ max_ = ...>
struct limited_int
```

**How it Works:**
- Constructor applies modulo: `val = ((val - min) % range) + min`
- Automatically wraps out-of-bounds values to the valid range
- Perfect for circular values (angles, modulo arithmetic)

**Example:**
```cpp
Deg360 deg360 = 510;  // Automatically becomes 150 (510 % 360)
```

**Limitation:**
- Works great for circular values, but semantically odd for asymmetric ranges

---

### Step 2: Better Output & Conversion

**File:** `include/limited_int_2.h`

**What:** Adds conversion between different `limited_int` types with proper scaling.

**Improvements:**
- ✅ Overloaded `operator<<` for better output display
- ✅ Template copy constructor for converting between ranges
- ✅ Linear scaling conversion: maps one range to another proportionally
- ✅ Handles asymmetric ranges better

**Example Conversion:**
```cpp
MilliM milliM = -567'000;        // Range: [-1M, 1M]
MicroM microM = milliM;           // Range: [-1G, 1G]
// Value scales proportionally: -567'000 → -567'000'000'000
```

**Limitation:**
- Allows invalid template combinations (e.g., `limited_int<int, 5, -3>` where min > max)
- No validation of template parameters

---

### Step 3: Template Parameter Validation

**File:** `include/limited_int_3.h`

**What:** Adds compile-time checks using `static_assert` to validate template parameters.

**Improvements:**
- ✅ Type checking: only integral types allowed
- ✅ Range checking: `min < max` required
- ✅ Sensibility check: at least one bound must differ from numeric limits

**Errors Caught at Compile Time:**
```cpp
// ERROR: min > max
limited_int<int, 5, -3> strange;

// ERROR: non-integral type
limited_int<double, 1.6, 3.1415> strange;

// ERROR: whole range not allowed
limited_int<bool, false, true> strange;
```

**Limitation:**
- Silently wraps out-of-bounds values using modulo
- No way to detect invalid assignments at compile time
- Circular scaling doesn't work well for non-circular ranges

---

### Step 4: Policy-Based Error Handling

**File:** `include/limited_int_4.h`

**What:** Introduces a **traits** system with pluggable error resolution policies.

**Three Resolution Policies:**

1. **`resolve_modulo`** (default for circular values)
   - Wraps values using modulo: `value = ((value - min) % range) + min`
   - Best for: angles, cyclic indices

2. **`resolve_invalid`** (for strict validation)
   - Sets an "invalid" sentinel value when out of range
   - Provides `isValid()` method to check state
   - Best for: detecting invalid operations

3. **`resolve_throw`** (for error-critical code)
   - Throws `std::out_of_range` exception
   - Best for: safety-critical systems needing strict validation

**Example:**
```cpp
typedef limited_int<int64_t, -1'000'000, 1'000'000,
    limited_int_traits<..., resolve_invalid, convert_scale>> MilliM;

MilliM m = 1'500'000;  // Out of range!
if (!m.isValid()) {
    cout << "Invalid value assigned!" << endl;
}
```

**Two Conversion Policies:**

1. **`convert_scale`** (default)
   - Linear scaling conversion between ranges
   - Proportional mapping: `(val - min_src) / range_src * range_dst`

2. **`convert_circular_scale`**
   - For circular ranges (angles)
   - Preserves circularity when converting between angle types

**Limitation:**
- Complex template syntax for type definitions
- Static assertions difficult to specialize

---

### Step 5: Exception-Safe with Enhanced Validation

**File:** `include/limited_int_5.h`

**What:** Refines Step 4 with type traits validation using explicit specialization.

**Improvements:**
- ✅ Explicit specialization of `is_out_of_bounds_resolver` (cleaner than SFINAE)
- ✅ Explicit specialization of `is_limited_int_converter`
- ✅ Better compile-time error messages
- ✅ More robust template parameter checking

**Type Traits System:**
```cpp
template< typename, typename = void >
struct is_out_of_bounds_resolver : std::false_type { };

template<>
struct is_out_of_bounds_resolver<resolve_modulo> : std::true_type { };
template<>
struct is_out_of_bounds_resolver<resolve_invalid> : std::true_type { };
template<>
struct is_out_of_bounds_resolver<resolve_throw> : std::true_type { };
```

**Cleaner Type Checking:**
```cpp
constexpr static INT_ invalid()
{
    static_assert(is_limited_int_converter<Converter>::value, 
                  "invalid limited_int_converter");
    static_assert(is_out_of_bounds_resolver<Resolver>::value, 
                  "invalid out_of_bounds_resolver");
    // ...
}
```

---

### Step 6: Full-Featured Implementation

**File:** `include/limited_int_6.h`

**What:** Complete, production-ready implementation with all features integrated.

**Features:**
- ✅ All three resolution policies
- ✅ Both conversion strategies
- ✅ Full template parameter validation
- ✅ Proper output formatting with validity indicator
- ✅ Exception handling for `resolve_throw` policy
- ✅ Set operations and STL compatibility testing

**Advanced Features:**

1. **Validity Indicator in Output:**
   ```cpp
   MilliM m = 1'500'000;  // Out of range
   cout << m;             // Prints: <INV> [-1000000,1000000]
   ```

2. **STL Container Support:**
   ```cpp
   std::set<MilliM> mmSet;
   for(int64_t v = -3; v < 3; v++) {
       mmSet.insert(v);
   }
   ```

3. **Loop Control with Validity:**
   ```cpp
   typedef limited_int<short, -10, 10, 
       limited_int_traits<short, -10, 10, resolve_invalid>> ShortCut;
   
   for(ShortCut i = 5; i.isValid(); i = ShortCut(i+1))
       cout << i << endl;
   ```

4. **Exception-Safe Loops:**
   ```cpp
   try {
       typedef limited_int<long, -10, 10, 
           limited_int_traits<long, -10, 10, resolve_throw>> LongJump;
       LongJump longJump = 13;  // Throws exception
   }
   catch(exception const & e) {
       cout << "Caught: " << e.what() << endl;
   }
   ```

---

## Learning Path

### Understanding the Progression

1. **Steps 0-1:** Learn the basic idea
   - See why templates help with type safety
   - Understand modulo-based wrapping

2. **Steps 2-3:** Add robustness
   - Learn template parameter validation with `static_assert`
   - Understand compile-time checking

3. **Steps 4-6:** Advanced design patterns
   - Learn policy-based design
   - Understand type traits
   - See how to build flexible, reusable templates

### Key Concepts Demonstrated

| Concept                 | Step | Purpose                          |
|-------------------------|------|----------------------------------|
| Template parameters     | 1    | Type and range specification     |
| Copy constructors       | 2    | Converting between types         |
| static_assert           | 3    | Compile-time validation          |
| Traits classes          | 4-6  | Pluggable policies and behaviors |
| Explicit specialization | 5    | Type trait implementation        |
| SFINAE (attempted)      | 6    | Advanced template techniques     |
| Exception handling      | 4, 6 | Error reporting via exceptions   |

---

## Building Your Own Limited Types

### Example 1: Temperature Limiter (Celsius, -50 to 50)

```cpp
typedef limited_int<int, -50, 50> Celsius;

Celsius temp = 100;  // Automatically wraps to range
cout << temp << endl; // Output: 50 [-50,50]
```

### Example 2: Percentage with Validation

```cpp
typedef limited_int<int, 0, 100,
    limited_int_traits<int, 0, 100, resolve_invalid>> Percentage;

Percentage p = 150;
if (!p.isValid()) {
    cout << "Invalid percentage!" << endl;
}
```

### Example 3: Angle Conversion (Degree to Radian)

```cpp
typedef limited_int<int64_t, 0, 359,
    limited_int_traits<int64_t, 0, 359, 
                       resolve_modulo, convert_circular_scale>> Degrees;

typedef limited_int<int64_t, 0, 6283,  // ~2π * 1000
    limited_int_traits<int64_t, 0, 6283,
                       resolve_modulo, convert_circular_scale>> MilliRadians;

Degrees d = 45;
MilliRadians r = d;  // Scales appropriately
```

---

## Files Overview

```
templateDemo/
├── README.md                    # This file
├── CMakeLists.txt              # Build configuration
├── src/
│   ├── CMakeLists.txt
│   └── main.cc                 # Entry point, selects STEP
├── include/
│   ├── limited_int_0.h         # Step 0: Plain ints
│   ├── limited_int_1.h         # Step 1: Basic template + modulo
│   ├── limited_int_2.h         # Step 2: Conversion + better output
│   ├── limited_int_3.h         # Step 3: Parameter validation
│   ├── limited_int_4.h         # Step 4: Policies
│   ├── limited_int_4_1.h       # Alternative Step 4
│   ├── limited_int_5.h         # Step 5: Traits refinement
│   ├── limited_int_6.h         # Step 6: Full featured
│   └── limited_int.h           # Consolidated header
└── build/                      # Build directory
```

---

## Exercises

1. **Create a new policy:** Write a `resolve_clamp` policy that clamps out-of-bounds values to the nearest boundary instead of wrapping or marking invalid.

2. **Add logging:** Modify `resolve_throw` to log all out-of-range assignments before throwing.

3. **Implement `resolve_saturate`:** Create a policy that sets values to the boundary (min or max) when out of range.

4. **Template specialization:** Add specializations for `bool` and `char` types with custom range validation.

5. **Performance test:** Measure the runtime overhead of each policy (resolve_modulo vs resolve_invalid vs resolve_throw).

---

## Further Reading

- C++ Static Assertions: https://en.cppreference.com/w/cpp/language/static_assert
- SFINAE and Type Traits: https://en.cppreference.com/w/cpp/types
- Policy-Based Design: https://en.wikipedia.org/wiki/Modern_C%2B%2B_Design
- Template Specialization: https://en.cppreference.com/w/cpp/language/template_specialization

