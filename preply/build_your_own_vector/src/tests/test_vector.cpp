#include <cassert>
#include <iostream>
#include "vector.h"

void test_push_back_grows() {
    IntVector v;
    // ####################
    // test:: empty()
    assert(v.empty() == true);
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    // test:: empty()
    assert(v.empty() == false);

    // ####################
    // test: check size is 100 after push_back
    assert(v.size() == 100);
    // test: check capacity is gt 100 after push_back
    assert(v.capacity() >= 100);
    for (int i = 0; i < 100; ++i)
    {
       // test: check item in each index after push_back
        assert(v[i] == i);
    }

    // ####################
    //test:: at()
    assert(v.at(0) == 0);
    assert(v.at(99) == 99);

    // ####################
    // test: pop_back()
    assert(v.size() == 100);
    v.pop_back();

    // ####################
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

    // ####################
    // negative test: check cannot shrink using reserve
    assert(v.capacity() >= 100);
    v.reserve(80) ;
    assert(v.capacity() >= 100);
    v.reserve(200) ;
    // test: check capacity is gt 200 after reserve
    assert(v.capacity() >= 200);


    // ####################
    // test index operator can assign values
    v[0] = 100;
    assert(v[0] == 100);

    // ####################
    // test: clear()
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() >= 200);

    // ####################
    // test: allocations
    IntVector v_new;
    for (int i = 0; i < 1000; ++i)
    {
        v_new.push_back(i);
    }
    assert(v_new.get_allocations() == 10);
    assert(v_new.size() == 1000);
    assert(v_new.capacity() == 1024);
}

int main()
{
    test_push_back_grows();
    std::cout << "All tests passed \n";
}
