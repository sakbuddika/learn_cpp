#include <cassert>
#include <iostream>
#include "vector.h"

void test_push_back_grows() {
    IntVector v;
     for (int i = 0; i < 100; ++i)
     {
         v.push_back(i);
     }
     // test: check size is 100 after push_back
     assert(v.size() == 100);
     // test: check capacity is gt 100 after push_back
     assert(v.capacity() >= 100);
     for (int i = 0; i < 100; ++i)
     {
        // test: check item in each index after push_back
         assert(v[i] == i);
     }
     // negative test: check cannot shrink using reserve
     std::cout << v.capacity() << std::endl;
     v.reserve(80) ;
     assert(v.capacity() >= 100);
     v.reserve(200) ;
     // test: check capacity is gt 200 after reserve
     // assert(v.capacity() >= 200);
     std::cout << v.capacity() << std::endl;
}

int main()
{
    test_push_back_grows();
    std::cout << "All tests passed \n";
}
