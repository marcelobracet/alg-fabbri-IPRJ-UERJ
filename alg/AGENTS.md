# Agent Instructions

## Important: Compilation Methods

**❌ Don't do this:**
```bash
gcc alg/sort-char/sort_char.cpp  # This will fail - no main() function
```

**✅ Use CMake (Recommended):**
```bash
mkdir -p build && cd build
cmake .. && make
./alg/sort-char/cmd/sort_char-cmd "hello world"
```

**✅ Manual compilation with main:**
```bash
gcc -o test alg/sort-char/sort_char.cpp alg/sort-char/cmd/main.cpp -I alg/sort-char
./test "hello world"
```

## Project Structure

- `sort-char/sort_char.cpp` - Contains only the `sort_char()` function
- `sort-char/cmd/main.cpp` - Contains the `main()` function for CLI
- `sort-char/tests/test_sort_char.cpp` - Contains test `main()` function
- `sort-char/benchmark/benchmark_sort_char.cpp` - Contains benchmark `main()`

## Current Implementation

- **Algorithm**: Bubble sort (O(n²) time complexity)
- **Function**: `void sort_char(char* v)`
- **Files**: Complete structure with proper main functions

