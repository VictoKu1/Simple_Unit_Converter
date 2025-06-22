# Number With Units - Part B

## Table of Contents
- [Task](#task)
- [Solution](#solution)
  - [Overview](#overview)
  - [Architecture](#architecture)
    - [Core Components](#core-components)
  - [Key Features](#key-features)
    - [1. Unit Management](#1-unit-management)
    - [2. Arithmetic Operations](#2-arithmetic-operations)
    - [3. Comparison Operations](#3-comparison-operations)
    - [4. I/O Operations](#4-io-operations)
  - [Implementation Details](#implementation-details)
    - [Unit Conversion Algorithm](#unit-conversion-algorithm)
    - [Memory Management](#memory-management)
    - [Error Handling](#error-handling)
  - [Usage Examples](#usage-examples)
  - [Testing Strategy](#testing-strategy)
  - [Build System](#build-system)
  - [Performance Characteristics](#performance-characteristics)
  
## Task

Write a class to manage numbers with units according to the instructions in Part A.

In Part B, you need to write a complete implementation. The implementation must pass all tests (60% of the grade):

```bash
make test
./test
```

Additionally, the code must successfully pass the readability test (20% of the grade):

```bash
make tidy
```

And the memory test (20% of the grade):

```bash
make valgrind
```

Furthermore, you must write a **main program** that demonstrates your solution.
The content of the program is your choice - be creative. The program will not be automatically tested but only during presentation.

You can check your grade using the command:

```bash
bash grade
```

## Solution

### Overview

This project implements a `NumberWithUnits` class that allows mathematical operations between numbers with different units, automatically handling unit conversions based on predefined relationships. The solution provides a robust, memory-safe implementation with comprehensive operator overloading.

### Architecture

#### Core Components

1. **NumberWithUnits Class** (`NumberWithUnits.hpp` & `NumberWithUnits.cpp`)
   - Manages a numeric value with an associated unit
   - Provides arithmetic and comparison operations
   - Handles unit conversions automatically

2. **Unit Conversion System**
   - Uses a static map-based graph structure for unit relationships
   - Supports transitive conversions (A→B→C enables A→C)
   - Maintains conversion coefficients bidirectionally

3. **Main Program** (`Main.cpp`)
   - Demonstrates the class functionality
   - Loads unit definitions from file
   - Shows conversion relationships

### Key Features

#### 1. Unit Management
- **Static Unit Dictionary**: Uses `map<string, map<string, double>>` to store conversion relationships
- **Transitive Closure**: Automatically computes all possible conversion paths
- **Bidirectional Conversions**: If 1 km = 1000 m, then 1 m = 0.001 km is automatically added

#### 2. Arithmetic Operations
The class overloads all standard arithmetic operators:
- **Addition/Subtraction**: `+`, `-`, `+=`, `-=`
- **Unary Operations**: `+`, `-`, `++`, `--` (both prefix and postfix)
- **Scalar Multiplication**: `*` (number × unit and unit × number)

#### 3. Comparison Operations
All comparison operators (`<`, `<=`, `>`, `>=`, `==`, `!=`) are implemented with:
- **Automatic Unit Conversion**: Compares values in the same unit
- **Tolerance Handling**: Uses 0.001 tolerance for floating-point comparisons
- **Type Safety**: Throws exceptions for incompatible units

#### 4. I/O Operations
- **Output Format**: `number[unit]` (e.g., `5.5[km]`)
- **Input Parsing**: Handles whitespace and bracket formatting
- **Error Handling**: Validates units during input

### Implementation Details

#### Unit Conversion Algorithm

```cpp
void put(string &unit1, string &unit2, double cof) {
    // Add direct conversion
    dic[unit1][unit2] = cof;
    dic[unit2][unit1] = (1 / cof);
    
    // Compute transitive conversions
    for (auto &u1 : dic[unit2]) {
        put(unit1, u1.first, cof * u1.second);
    }
    for (auto &u2 : dic[unit1]) {
        put(unit2, u2.first, (1 / cof) * u2.second);
    }
}
```

This algorithm ensures that when a new conversion is added, all possible paths through the conversion graph are computed and stored.

#### Memory Management

- **RAII Principles**: All resources are managed automatically
- **No Raw Pointers**: Uses standard containers and smart memory management
- **Exception Safety**: Operations are exception-safe with proper cleanup

#### Error Handling

- **Invalid Units**: Throws `invalid_argument` for undefined units
- **Incompatible Conversions**: Throws descriptive errors for non-convertible units
- **Input Validation**: Validates format and unit existence during parsing

### Usage Examples

```cpp
// Load unit definitions
ifstream units_file{"units.txt"};
NumberWithUnits::read_units(units_file);

// Create numbers with units
NumberWithUnits distance1(5, "km");
NumberWithUnits distance2(1000, "m");

// Arithmetic operations
NumberWithUnits sum = distance1 + distance2;  // 6[km]
NumberWithUnits diff = distance1 - distance2; // 4[km]

// Comparisons
bool is_greater = distance1 > distance2;      // true

// Scalar operations
NumberWithUnits doubled = distance1 * 2;      // 10[km]
```

### Testing Strategy

The project includes comprehensive testing through:
1. **Unit Tests**: Multiple test suites covering all operations
2. **Memory Testing**: Valgrind integration for leak detection
3. **Code Quality**: Clang-tidy for static analysis
4. **Automated Grading**: Script-based evaluation system

### Build System

The project uses a Makefile with targets for:
- **Compilation**: `make main` or `make test1/2/3`
- **Testing**: `make test`
- **Memory Analysis**: `make valgrind`
- **Code Quality**: `make tidy`
- **Cleanup**: `make clean`

### Performance Characteristics

- **Time Complexity**: O(1) for direct conversions, O(V+E) for transitive closure computation
- **Space Complexity**: O(V²) for storing all possible conversion pairs
- **Memory Efficiency**: Minimal overhead with efficient data structures

This implementation provides a robust, efficient, and user-friendly solution for handling numbers with units, suitable for scientific calculations, engineering applications, and educational purposes.
