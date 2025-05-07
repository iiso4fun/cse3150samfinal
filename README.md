
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
````

## Build & Run Demo

```bash
g++ -std=c++17 -pthread main.cpp -o demo
./demo
```

## Demo Run & Expected Output

```bash
# Compile and run demo
g++ -std=c++17 -pthread main.cpp -o demo
./demo
```

Expected console output (addresses will vary):

```
ControlTimedSharedPtr 0xXXXXXXXXXXXX start: 0 ms
myNode.get() address: <0xXXXXXXXXXXXX>
myNode.use_count(): 2
myOtherNode.use_count(): 2
myNode.get() address: <0xXXXXXXXXXXXX>
The ptr should have expired:
myNode.get() address: <Yeo! Expired 0>
-----------
ControlTimedSharedPtr 0xYYYYYYYYYYYY start: 0 ms
0xYYYYYYYYYYYY
p.use_count(): 1
p.use_count(): 2
q.use_count(): 2
ControlTimedSharedPtr 0xYYYYYYYYYYYY end: 0 ms
ControlTimedSharedPtr 0xXXXXXXXXXXXX end: 150 ms
```

```
```
