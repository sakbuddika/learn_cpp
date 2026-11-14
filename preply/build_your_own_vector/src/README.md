
## How to build your own vector

This is a C++ project to build and test a our own version of std::vector - a growable array - using nothing but raw memory and pointers.
This project covers "low-level" techniques that matters in real C++ project.

- How objects are arranged in memory
- Who owns a piece of memory and who is responsible of allocating and deallocating it.
- The difference between allocating memory and creating objects.
- What happens when an object is moved or copied.
- How to use template to create a blue-print of code to work with any type.

### Ground Rules

1. Not allowed inside your vector implementation: std::vector, std::unique_ptr,
std::shared_ptr, std::allocator, std::array, std::uninitialized_copy and friends.
The point is to do the memory work yourself.
2. Allowed: std::size_t, std::move, std::swap, std::forward, exceptions such as
std::out_of_range, and the <new> header. In your tests you may use anything you like,
including std::vector for comparison.
3. Always compile with warnings and sanitizers turned on (see Setup below). A program that “seems to work” but makes the sanitizer complain is not finished yet.
4. Commit often. At least one commit per part, with a meaningful message. I want to see how the code evolved, not just the end result.

### Setup

#### Create a new Git repository on GitHub or GitLab with this layout:

    build_your_own_vector/
        README.md
        src/
            CMakeLists.txt
            include/
                CMakeLists.txt
                vector.h
                vector.cpp
            tests/
                CMakeLists.txt
                tracer.h
                test_vector.cpp

#### Command to compile

*g++ -std=c++17 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -Iinclude tests/test_vector.cpp -o run_tests*

**Use g++ or clang++, not gcc or clang.**

### CMake

For the real project, use CMake. Here is a setup for the layout above.

#### src/CMakeLists.txt

`cmake_minimum_required(VERSION 3.16)`
`project(build_your_own_vector CXX)`

`set(CMAKE_CXX_STANDARD 17)`
`set(CMAKE_CXX_STANDARD_REQUIRED ON)`
`set(CMAKE_CXX_EXTENSIONS OFF)`

`add_compile_options(-Wall -Wextra -Wpedantic`
                `-fsanitize=address,undefined)`
`add_link_options(-fsanitize=address,undefined)`

`add_subdirectory(include)`
`add_subdirectory(tests)`

#### src/include/CMakeLists.txt

`add_library(vector vector.cpp)`
`target_include_directories(vector PUBLIC .)`

#### src/tests/CMakeLists.txt

`add_executable(run_tests test_vector.cpp)`
`target_link_libraries(run_tests PRIVATE vector)`

#### Build and run from the folder that contains src/:

`cmake -S src -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++`
`cmake --build build`
`./build/tests/run_tests`

### Sanity Check

lets see whether our compiler catches if we do something wrong.
`int main() {`
    `int* p = new int[3];`
    `p[3] = 42;` // one past the end!
    `delete[] p;`
`}`

You should get a red AddressSanitizer: heap-buffer-overflow report. If you do, your setup is working.
Lets remove the bug and continue.

### Testing

Few tips for testing the software.

- Keep tests independent, for an example each test function creates its own vector so that test failures are not cascading.
- Make sure every test has the capability to fail, for an example a test that gets no exception when it should fail.

#### Example Test

`#include <cassert>`
`#include <iostream>`
`#include "vector.h"`
`void test_push_back_grows() {`
    `Vector<int> v;`
    `for (int i = 0; i < 100; ++i) {`
        `v.push_back(i);`
    `}`
    `assert(v.size() == 100);`
    `assert(v.capacity() >= 100);`
    `for (int i = 0; i < 100; ++i) {`
        `assert(v[i] == i);`
    `}`
`}`
`int main() {`
    `test_push_back_grows();`
    `std::cout << "All tests passed\n";`:
`}`

**Note: assert does nothing when NDEBUG is defined (typical for release builds)**

#### Allocations

Total allocations happens for 1000 push_back calls with doubling is: 10
Size: 1000
Capacity: 1024


Total allocations happens for 1000 push_back calls with growing the capacity by just 1 each time is: 999
Size: 1000
Capacity: 1000


#### Copying without copy constructor

When trying to copy without a copy constructor we are doing a something called a shallow copy where both a and b now points to the same memory location. And during object destruction of a and b. One call will free up the memory of that location and second call to free up the memory will throw an error.

`IntVector a;`
`a.push_back(1);`
`a.push_back(2);`
`IntVector b = a;`

*==7889==ERROR: AddressSanitizer: attempting double-free on 0x5020000000f0 in thread T0:*
    *#0 0x77eb83cff1f8 in operator delete[](void*) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:155*
    *#1 0x5aea330d41e7 in IntVector::~IntVector() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/include/vector.cpp:11*
    *#2 0x5aea330d3a2f in test_copy() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:86*
    *#3 0x5aea330d3bec in main /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:97*
    *#4 0x77eb82c2a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58*
    *#5 0x77eb82c2a28a in __libc_start_main_impl ../csu/libc-start.c:360*
    *#6 0x5aea330d24a4 in _start (/home/sak/git/learn_cpp/preply/build_your_own_vector/build/tests/run_tests+0x74a4) (BuildId: 2297b202d5b2282187e41c31c36887d9e417eb29)*
    *0x5020000000f0 is located 0 bytes inside of 8-byte region [0x5020000000f0,0x5020000000f8) freed by thread T0 here:*
    *#0 0x77eb83cff1f8 in operator delete[](void*) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:155*
    *#1 0x5aea330d41e7 in IntVector::~IntVector() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/include/vector.cpp:11*
    *#2 0x5aea330d3a20 in test_copy() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:86*
    *#3 0x5aea330d3bec in main /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:97*
    *#4 0x77eb82c2a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58*
    *#5 0x77eb82c2a28a in __libc_start_main_impl ../csu/libc-start.c:360*
    *#6 0x5aea330d24a4 in _start (/home/sak/git/learn_cpp/preply/build_your_own_vector/build/tests/run_tests+0x74a4) (BuildId: 2297b202d5b2282187e41c31c36887d9e417eb29)*
    *previously allocated by thread T0 here:*
    *#0 0x77eb83cfe6c8 in operator new[](unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:98*
    *#1 0x5aea330d4bd4 in IntVector::reserve(unsigned long) /home/sak/git/learn_cpp/preply/build_your_own_vector/src/include/vector.cpp:48*
    *#2 0x5aea330d472c in IntVector::push_back(int) /home/sak/git/learn_cpp/preply/build_your_own_vector/src/include/vector.cpp:34*
    *#3 0x5aea330d3711 in test_copy() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:81*
    *#4 0x5aea330d3bec in main /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:97*
    *#5 0x77eb82c2a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58*
    *#6 0x77eb82c2a28a in __libc_start_main_impl ../csu/libc-start.c:360*
    *#7 0x5aea330d24a4 in _start (/home/sak/git/learn_cpp/preply/build_your_own_vector/build/tests/run_tests+0x74a4) (BuildId: 2297b202d5b2282187e41c31c36887d9e417eb29)*
*SUMMARY: AddressSanitizer: double-free ../../../../src/libsanitizer/asan/asan_new_delete.cpp:155 in operator delete[](void*)*
*==7889==ABORTING*


#### Why is template code normally lives in headers.

Template code gets converted to actual code during complile time, and the compilation for templates don't happen until the templates are in use.
In order for this to happen you need the full definition of the template in the header file. Based on where it used the template code will be copied to the source file and convert to support expected type. With templates it can create large header files and longer compilation time. But maintaining and reading the code will be easy with templates.

#### Copying primitive types vs complex types like strings

Copying string is not the same as copying bytes, because when copying strings you copy a pointer to the string. This makes two buffers keeping the same addresses and cause issues during accessing and releasing memory.
so you can't use memcpy without modifications.

Tracer output before fixing

*Tracer::alive: 1*
*Tracer::default_constructed: 0*
*Tracer::alive: 1*
*All tests passed*

Our tracer seems to be alive even it should have gone away.
The issue is `new T[n]` does two things it allocates memory and creates n objects. A real vector must do those two steps separately

#### Creating a iterator

When you want to use range based loops with the vector it looks for two methods `begin()` (which returns a pointer to the begining of the vector) and `end()` (which returns a pointer to one item pass the vector).

We created a seperate class called VectorIterator and created an alias called Iterator to that in the Vector class. In the VectorIterator class we created mandatory operators like ==, !=, ++, * so that the range based loop works with our version of Vector.
