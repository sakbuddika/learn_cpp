Allocations

Total allocations happens for 1000 push_back calls with doubling is: 10
Size: 1000
Capacity: 1024


Total allocations happens for 1000 push_back calls with growing the capacity by just 1 each time is: 999
Size: 1000
Capacity: 1000


Copying without copy constructor

When trying to copy without a copy constructor we are doing a something called a shallow copy where both a and b now points to the same memory location. And during object destruction of a and b. One call will free up the memory of that location and second call to free up the memory will throw an error.

```
IntVector a;
a.push_back(1);
a.push_back(2);
IntVector b = a;
```

99
=================================================================
==7889==ERROR: AddressSanitizer: attempting double-free on 0x5020000000f0 in thread T0:
    #0 0x77eb83cff1f8 in operator delete[](void*) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:155
    #1 0x5aea330d41e7 in IntVector::~IntVector() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/include/vector.cpp:11
    #2 0x5aea330d3a2f in test_copy() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:86
    #3 0x5aea330d3bec in main /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:97
    #4 0x77eb82c2a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #5 0x77eb82c2a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #6 0x5aea330d24a4 in _start (/home/sak/git/learn_cpp/preply/build_your_own_vector/build/tests/run_tests+0x74a4) (BuildId: 2297b202d5b2282187e41c31c36887d9e417eb29)

0x5020000000f0 is located 0 bytes inside of 8-byte region [0x5020000000f0,0x5020000000f8)
freed by thread T0 here:
    #0 0x77eb83cff1f8 in operator delete[](void*) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:155
    #1 0x5aea330d41e7 in IntVector::~IntVector() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/include/vector.cpp:11
    #2 0x5aea330d3a20 in test_copy() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:86
    #3 0x5aea330d3bec in main /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:97
    #4 0x77eb82c2a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #5 0x77eb82c2a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #6 0x5aea330d24a4 in _start (/home/sak/git/learn_cpp/preply/build_your_own_vector/build/tests/run_tests+0x74a4) (BuildId: 2297b202d5b2282187e41c31c36887d9e417eb29)

previously allocated by thread T0 here:
    #0 0x77eb83cfe6c8 in operator new[](unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:98
    #1 0x5aea330d4bd4 in IntVector::reserve(unsigned long) /home/sak/git/learn_cpp/preply/build_your_own_vector/src/include/vector.cpp:48
    #2 0x5aea330d472c in IntVector::push_back(int) /home/sak/git/learn_cpp/preply/build_your_own_vector/src/include/vector.cpp:34
    #3 0x5aea330d3711 in test_copy() /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:81
    #4 0x5aea330d3bec in main /home/sak/git/learn_cpp/preply/build_your_own_vector/src/tests/test_vector.cpp:97
    #5 0x77eb82c2a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #6 0x77eb82c2a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #7 0x5aea330d24a4 in _start (/home/sak/git/learn_cpp/preply/build_your_own_vector/build/tests/run_tests+0x74a4) (BuildId: 2297b202d5b2282187e41c31c36887d9e417eb29)

SUMMARY: AddressSanitizer: double-free ../../../../src/libsanitizer/asan/asan_new_delete.cpp:155 in operator delete[](void*)
==7889==ABORTING


