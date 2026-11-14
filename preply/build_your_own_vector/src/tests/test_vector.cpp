#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <new>
#include <string>
#include <utility>
#include "vector.h"
#include "tracer.h"

static int allocations = 0;
static int deallocations = 0;

void* operator new(const std::size_t size)
{
    allocations++;
    if (void* p = std::malloc(size)) {
        return p;
    }
    throw std::bad_alloc{};
}

// ::operator delete(nullptr) is allowed and does nothing, but it still
// calls this function. Only count real frees, otherwise moved-from and
// empty vectors inflate the count and can hide a leak.
void operator delete(void* p) noexcept
{
    if (p != nullptr) {
        deallocations++;
    }
    std::free(p);
}

void operator delete(void* p, std::size_t) noexcept
{
    if (p != nullptr) {
        deallocations++;
    }
    std::free(p);
}

namespace {
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
    assert(v.get_allocations() == 11);
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
    assert(v.get_allocations() == 11);
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
    v[0] = std::to_string(100);
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(std::move(std::to_string(i)));
    }
    // test index operator can assign values
    v[0] = std::to_string(100);
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
    assert(v.get_allocations() == 11);
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
    assert(e[0] == "plugh");
    assert(e[1] == "xyzzy");
#pragma GCC diagnostic pop
}

void test_tracer()
{
    Tracer::reset();
    {
        Vector<Tracer> t1;
        t1.reserve(100);
        t1.push_back(Tracer());
        assert(Tracer::alive == 1);
        assert(Tracer::default_constructed == 1);
        assert(Tracer::copies == 0);
        assert(Tracer::moves == 1);
        assert(t1.size() == 1);
        assert(t1.capacity() == 100);
        assert(t1.get_allocations() == 1);
        Vector<Tracer> t2;
        t2.reserve(100);
        t2.push_back(Tracer(7));
        assert(Tracer::alive == 2);
        assert(Tracer::default_constructed == 1);
        assert(Tracer::copies == 0);
        assert(Tracer::moves == 2);
        assert(t2.size() == 1);
        assert(t2.capacity() == 100);
        assert(t2.get_allocations() == 1);
    }
    assert(Tracer::alive == 0);
}

void test_range_based_loops()
{
    Vector<std::string> names;
    names.push_back("Ada");
    names.push_back("Bjarne");
    names.push_back("C++");
    names.pop_back();
    int i = 0;
    for (const auto& name : names) {
        assert(name == names[i]);
        i++;
    }
}

void test_traditional_iterators()
{
    Vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.pop_back();
    int i = 0;
    for (Vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++) {
        assert(*it == numbers[i]);
        i++;
    }
}

// Move assignment must destroy the strings the target already holds
// before it frees the target's buffer. Freeing only the buffer leaks
// the heap memory of every long string in it.
void test_move_assignment_leak()
{
    // Longer than 15 characters: the text lives on the heap, not inside
    // the std::string object (small string optimisation).
    const std::string long_text =
        "This string is too long for the small string optimisation.";

    // Only count what happens inside the scope below.
    const int allocations_before = allocations;
    const int deallocations_before = deallocations;
    {
        Vector<std::string> target;
        target.push_back(long_text);  // copy: allocates the text
        target.push_back(long_text);  // copy: allocates the text

        // Different contents, so the 'if (*this != other)' check in
        // move assignment is true and the assignment really happens.
        Vector<std::string> source;
        source.push_back("short");

        target = std::move(source);  // target's two strings must be destroyed
    }  // both vectors are destroyed here
    const int allocated = allocations - allocations_before;
    const int freed = deallocations - deallocations_before;

    std::printf("move assignment: %d allocations, %d deallocations, "
                "%d leaked\n", allocated, freed, allocated - freed);
    std::fflush(stdout);  // a failing assert aborts and drops unflushed output
    assert(allocated == freed);
}
} // anonymous namespace

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
    test_tracer();
    test_range_based_loops();
    test_traditional_iterators();
    test_move_assignment_leak();
    std::cout << "All tests passed \n";
}
