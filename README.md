# cse3150samfinal


# TimedSharedPtr Final Exam Project

## Description
A header-only `TimedSharedPtr<T>` that mimics `std::shared_ptr<T>` but whose `get()` returns `nullptr` once a specified lifetime (in milliseconds) has elapsed. It also logs “start” and “end” messages on construction and destruction of each control block.

## Files
- **TimedSharedPtr.hpp**  
- **test_timed_shared_ptr.cpp**  
- **main.cpp**  
- **doctest.h**  
- **README.md** (this file)

## Build & Run Unit Tests
```bash
g++ -std=c++17 -pthread test_timed_shared_ptr.cpp -o tests
./tests
