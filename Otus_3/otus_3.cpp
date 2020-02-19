#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <list>
#include "my_allocator.h"
#include "factorial.h"
#include "my_list.h"
//-----------------------------------------------------------------------------
void TestAllocatorMap()
{

//     auto v = std::vector<int>();
//    v.push_back(1222);
    using mkey = std::size_t;
    using mvalue = std::size_t;
//     std::list<int> lists;
//     std::array<int, 15> test;
    auto m = std::map<mkey, mvalue, std::less<mkey>, MapAllocator<std::pair<const mkey, mvalue>, 10>>();
    int i = 0;
    for (; i < 10; ++i) {
        m[i] = i * 10;
        std::cout << m[i] << std::endl;
    }
    int stop1 = 0;
}
//-----------------------------------------------------------------------------
//  int main(int, char *[])
//  {
//      std::cout << "Start Program" << std::endl;
//      long long count=0;
//      for (int i = 0; i < 5000000; ++i) {
//          TestAllocator();
//          ++count;
//          if ((count % 10000)==0) {
//              std::cout << count << std::endl;
//          }
//      }
//      std::cout << "Close Program" << std::endl;
//      return 0;
//  }
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
int main(int, char *[])
{
    TNode<int> a(-22);
    TNode<int> a2 = a;
    TNode<int> a3 = TNode<int>(a);


    auto myList = MyList<std::uint64_t>();
    //return 0;
    myList.Add(2);
    myList.Add(7);
    myList.Add(9);
    myList.Add(22);
    myList.Add(1);
    myList.Add(1);
    auto listSize = myList.Size();
    auto listData = myList.GetData();

    MyListIterator<MyList<std::uint64_t>> iter = MyListIterator<MyList<std::uint64_t>>(myList);
    int stop1 = 0;
//    auto listNode = myList.GetNode(3);
    //auto listData = myList.GetData();


    //
    //std::array<int, 5> a;
    //std::list<int> a1;
    ////a.front
    ////MyList<int, std::allocator<int>> test;
    //std::cout << "Start Program" << std::endl;
    //TestAllocatorMap();
    ////TestAllocatorVector();
    //std::cout << "Close Program" << std::endl;
    return 0;
}

