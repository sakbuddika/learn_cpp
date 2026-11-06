#include <cassert>
#include <iostream>
#include "vector.h"

void test_empty_vector()
{
    Vector<int> v;
    //test:: at() out of bound
    bool threw = false;
    try
    {
        v.at(0);
    }
    catch(const std::out_of_range &)
    {
        threw = true;
    }
    assert(threw);
    v.reserve(10);
}

void test_push_back()
{
    Vector<int> v;
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

void test_pop_back()
{
    Vector<int> v;
    v.pop_back();
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    assert(v.size() == 100);
    v.pop_back();
    //test:: at() out of bound
    bool threw = false;
    try
    {
        v.at(99);
    }
    catch(const std::out_of_range &)
    {
        threw = true;
    }
    assert(threw);
    assert(v.size() == 99);
    assert(v.at(98) == 98);
}

void test_reserve()
{
    Vector<int> v;
    v.reserve(10) ;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    // negative test: check cannot shrink using reserve
    assert(v.capacity() >= 100);
    v.reserve(80) ;
    assert(v.capacity() >= 100);
    v.reserve(200) ;
    assert(v.capacity() >= 200);
}

void test_operators()
{
    Vector<int> v;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    v[0] = 100;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    // test index operator can assign values
    v[0] = 100;
    assert(v[0] == 100);
}

void test_clear()
{
    Vector<int> v;
    v.clear();
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    v.reserve(200) ;
    v.clear();
    bool threw = false;
    try
    {
        v.at(0);
    }
    catch(const std::out_of_range &)
    {
        threw = true;
    }
    assert(threw);
    assert(v.size() == 0);
    assert(v.capacity() >= 200);
}

void test_allocations()
{
    Vector<int> v;
    assert(v.get_allocations() == 0);
    for (int i = 0; i < 1000; ++i)
    {
        v.push_back(i);
    }
    assert(v.get_allocations() == 10);
    assert(v.size() == 1000);
    assert(v.capacity() == 1024);
}

void test_copy()
{
    Vector<int> a;
    a.push_back(1);
    a.push_back(2);
    // copy constructor
    Vector<int> b = a;
    b[0] = 99;
    assert(a[0] == 1);
    assert(b[0] == 99);
    Vector<int> c;
    c.push_back(1);
    c.push_back(2);
    Vector<int> d;
    // copy assignment
    d = c;
    d[0] = 99;
    assert(c[0] == 1);
    assert(d[0] == 99);
    // copy empty vector
    Vector<int> e;
    Vector<int> f = e;
}

void test_move()
{
    Vector<int> a;
    a.push_back(1);
    a.push_back(2);
    // move constructor
    Vector<int> b = std::move(a);
    assert(b[0] == 1);
    assert(b[1] == 2);
    // move assignment
    Vector<int> c;
    c.push_back(1);
    c.push_back(2);
    Vector<int> d;
    d = std::move(c);
    assert(d[0] == 1);
    assert(d[1] == 2);
    // self assignment
    Vector<int> e;
    e.push_back(1);
    e.push_back(2);
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wself-move"
    e = std::move(e);
    assert(e[0] == 1);
    assert(e[1] == 2);
    #pragma GCC diagnostic pop
}

int main()
{
    test_empty_vector();
    test_push_back();
    test_pop_back();
    test_reserve();
    test_operators();
    test_clear();
    test_allocations();
    test_copy();
    test_move();
    std::cout << "All tests passed \n";
}
