#include <cassert>
#include <iostream>
#include "vector.h"

void test_push_back_grows() {
    Vector<int> v;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    assert(v.size() == 100);
    assert(v.capacity() >= 100);
    for (int i = 0; i < 100; ++i)
    {
        assert(v[i] == i);
    }
}

int main()
{
    test_push_back_grows();
    std::cout << "All tests passed \n";
}
