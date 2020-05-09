#pragma once
#include "my_allocator.h"
#include "my_list.h"
#include "factorial.h"
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <list>
//-----------------------------------------------------------------------------
namespace otus
{
    //-----------------------------------------------------------------------------
    using StandardMap = std::map<std::size_t, std::size_t>;
    using CustomMap = std::map<std::size_t, std::size_t, std::less<std::size_t>, MyAllocator<std::pair<const std::size_t, std::size_t>, 10>>;
    using StandardMyList = MyList<int>;
    using CustomMyList = MyList<int, MyAllocator<int>>;
    //-----------------------------------------------------------------------------
    void FillMap(StandardMap& aMap)
    {
        for (int i = 0; i <= 9; ++i) {
            aMap.insert({ i, Factorial(i) });
        }
    }
    //-----------------------------------------------------------------------------
    void FillMap(CustomMap& aMap)
    {
        for (int i = 0; i <= 9; ++i) {
            aMap.insert({ i, Factorial(i) });
        }
    }
    //-----------------------------------------------------------------------------
    void FillMyList(StandardMyList& aList)
    {
        for (int i = 0; i <= 9; ++i) {
            aList.Add(i);
        }
    }
    //-----------------------------------------------------------------------------
    void FillMyList(CustomMyList& aList)
    {
        for (int i = 0; i <= 9; ++i) {
            aList.Add(i);
        }
    }
    //-----------------------------------------------------------------------------
    void FactorialTest()
    {
        static_assert(Factorial(0) == 1);
        static_assert(Factorial(1) == 1);
        static_assert(Factorial(2) == 2);
        static_assert(Factorial(3) == 6);
        static_assert(Factorial(4) == 24);
        static_assert(Factorial(5) == 120);
        static_assert(Factorial(6) == 720);
        static_assert(Factorial(7) == 5040);
        static_assert(Factorial(8) == 40320);
        static_assert(Factorial(9) == 362880);
    }
    //-----------------------------------------------------------------------------
}
