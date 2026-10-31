#include <cassert>
#include <iostream>
#include "vector.h"

void test_push_back(IntVector& v)
{
    assert(v.empty() == true);
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    assert(v.empty() == false);

    assert(v.size() == 100);
    assert(v.capacity() >= 100);
    for (int i = 0; i < 100; ++i)
    {
        assert(v[i] == i);
    }

    assert(v.at(0) == 0);
    assert(v.at(99) == 99);
}

void test_pop_back(IntVector& v)
{
    assert(v.size() == 100);
    v.pop_back();

    //test:: at() out of bound
    try
    {
        v.at(99);
    }
    catch(std::out_of_range const& ex)
    {
        assert(strcmp(ex.what(),"Index is out of bound") == 0);
    }
    assert(v.size() == 99);
    assert(v.at(98) == 98);
}

void test_reserve(IntVector& v)
{
    // negative test: check cannot shrink using reserve
    assert(v.capacity() >= 100);
    v.reserve(80) ;
    assert(v.capacity() >= 100);
    v.reserve(200) ;
    assert(v.capacity() >= 200);
}

void test_operators(IntVector& v)
{
    // test index operator can assign values
    v[0] = 100;
    assert(v[0] == 100);
}

void test_clear(IntVector& v)
{
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() >= 200);
}

void test_allocations()
{
    IntVector v;
    for (int i = 0; i < 1000; ++i)
    {
        v.push_back(i);
    }
    assert(v.get_allocations() == 10);
    assert(v.size() == 1000);
    assert(v.capacity() == 1024);
}

void test_copy() {
    IntVector a;
    a.push_back(1);
    a.push_back(2);
    IntVector b = a;
    b[0] = 99;
    assert(a[0] == 1);
    assert(b[0] == 99);
    std::cout << b[0] << "\n";
    IntVector c;
    c = a;
    c[0] = 99;
    assert(a[0] == 1);
    assert(b[0] == 99);
}

int main()
{
    IntVector v;
    test_push_back(v);
    test_pop_back(v);
    test_reserve(v);
    test_operators(v);
    test_clear(v);
    test_allocations();
    test_copy();
    std::cout << "All tests passed \n";
}
