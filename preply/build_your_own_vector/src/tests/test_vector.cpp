#include <cassert>
#include <iostream>
#include <string>
#include "vector.h"

void test_int_empty_vector()
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

void test_int_push_back()
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

void test_int_pop_back()
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

void test_int_reserve()
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

void test_int_operators()
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

void test_int_clear()
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

void test_int_allocations()
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

void test_int_copy()
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

void test_int_move()
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

void test_double_empty_vector()
{
    Vector<double> v;
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

void test_double_push_back()
{
    Vector<double> v;
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

void test_double_pop_back()
{
    Vector<double> v;
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

void test_double_reserve()
{
    Vector<double> v;
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

void test_double_operators()
{
    Vector<double> v;
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

void test_double_clear()
{
    Vector<double> v;
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

void test_double_allocations()
{
    Vector<double> v;
    assert(v.get_allocations() == 0);
    for (int i = 0; i < 1000; ++i)
    {
        v.push_back(i);
    }
    assert(v.get_allocations() == 10);
    assert(v.size() == 1000);
    assert(v.capacity() == 1024);
}

void test_double_copy()
{
    Vector<double> a;
    a.push_back(1.1);
    a.push_back(2.2);
    // copy constructor
    Vector<double> b = a;
    b[0] = 99.99;
    assert(a[0] == 1.1);
    assert(b[0] == 99.99);
    Vector<double> c;
    c.push_back(1.1);
    c.push_back(2.2);
    Vector<double> d;
    // copy assignment
    d = c;
    d[0] = 99.99;
    assert(c[0] == 1.1);
    assert(d[0] == 99.99);
    // copy empty vector
    Vector<double> e;
    Vector<double> f = e;
}

void test_double_move()
{
    Vector<double> a;
    a.push_back(1.1);
    a.push_back(2.2);
    // move constructor
    Vector<double> b = std::move(a);
    assert(b[0] == 1.1);
    assert(b[1] == 2.2);
    // move assignment
    Vector<double> c;
    c.push_back(1.1);
    c.push_back(2.2);
    Vector<double> d;
    d = std::move(c);
    assert(d[0] == 1.1);
    assert(d[1] == 2.2);
    // self assignment
    Vector<double> e;
    e.push_back(1.1);
    e.push_back(2.2);
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wself-move"
    e = std::move(e);
    assert(e[0] == 1.1);
    assert(e[1] == 2.2);
    #pragma GCC diagnostic pop
}

void test_string_empty_vector()
{
    Vector<std::string> v;
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

void test_string_push_back()
{
    Vector<std::string> v;
    assert(v.empty() == true);
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(std::move(std::to_string(i)));
    }
    assert(v.empty() == false);

    assert(v.size() == 100);
    assert(v.capacity() >= 100);
    for (int i = 0; i < 100; ++i)
    {
        assert(v[i] == std::to_string(i));
    }

    assert(v.at(0) == std::to_string(0));
    assert(v.at(99) == std::to_string(99));
}

void test_string_pop_back()
{
    Vector<std::string> v;
    v.pop_back();
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(std::move(std::to_string(i)));
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
    assert(v.at(98) == std::to_string(98));
}

void test_string_reserve()
{
    Vector<std::string> v;
    v.reserve(10) ;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(std::move(std::to_string(i)));
    }
    // negative test: check cannot shrink using reserve
    assert(v.capacity() >= 100);
    v.reserve(80) ;
    assert(v.capacity() >= 100);
    v.reserve(200) ;
    assert(v.capacity() >= 200);
}

void test_string_operators()
{
    Vector<std::string> v;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(std::move(std::to_string(i)));
    }
    v[0] = 100;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(std::move(std::to_string(i)));
    }
    // test index operator can assign values
    v[0] = 100;
    assert(v[0] == std::to_string(100));
}

void test_string_clear()
{
    Vector<std::string> v;
    v.clear();
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(std::move(std::to_string(i)));
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

void test_string_allocations()
{
    Vector<std::string> v;
    assert(v.get_allocations() == 0);
    for (int i = 0; i < 1000; ++i)
    {
        v.push_back(std::move(std::to_string(i)));
    }
    assert(v.get_allocations() == 10);
    assert(v.size() == 1000);
    assert(v.capacity() == 1024);
}

void test_string_copy()
{
    Vector<std::string> a;
    a.push_back(std::move("foo"));
    a.push_back(std::move("bar"));
    // copy constructor
    Vector<std::string> b = a;
    b[0] = "baz";
    assert(a[0] == "foo");
    assert(b[0] == "baz");
    Vector<std::string> c;
    c.push_back(std::move("qux"));
    c.push_back(std::move("quux"));
    Vector<std::string> d;
    // copy assignment
    d = c;
    d[0] = "corge";
    assert(c[0] == "qux");
    assert(d[0] == "corge");
    // copy empty vector
    Vector<std::string> e;
    Vector<std::string> f = e;
}

void test_string_move()
{
    Vector<std::string> a;
    a.push_back(std::move("grault"));
    a.push_back(std::move("garply"));
    // move constructor
    Vector<std::string> b = std::move(a);
    assert(b[0] == "grault");
    assert(b[1] == "garply");
    // move assignment
    Vector<std::string> c;
    c.push_back(std::move("waldo"));
    c.push_back(std::move("fred"));
    Vector<std::string> d;
    d = std::move(c);
    assert(d[0] == "waldo");
    assert(d[1] == "fred");
    // self assignment
    Vector<std::string> e;
    e.push_back(std::move("plugh"));
    e.push_back(std::move("xyzzy"));
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wself-move"
    e = std::move(e);
    assert(e[0] == "plaugh");
    assert(e[1] == "xyzzy");
    #pragma GCC diagnostic pop
}

int main()
{
    test_int_empty_vector();
    test_int_push_back();
    test_int_pop_back();
    test_int_reserve();
    test_int_operators();
    test_int_clear();
    test_int_allocations();
    test_int_copy();
    test_int_move();
    test_double_empty_vector();
    test_double_push_back();
    test_double_pop_back();
    test_double_reserve();
    test_double_operators();
    test_double_clear();
    test_double_allocations();
    test_double_copy();
    test_double_move();
    test_string_empty_vector();
    test_string_push_back();
    test_string_pop_back();
    test_string_reserve();
    test_string_operators();
    test_string_clear();
    test_string_allocations();
    test_string_copy();
    test_string_move();
    std::cout << "All tests passed \n";
}
