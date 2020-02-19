#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <list>
#include "my_allocator.h"
#include "factorial.h"
#include "my_list.h"
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
int main(int, char *[])
{
    TNode<int> a(-22);
    TNode<int> a2 = a;
    TNode<int> a3 = TNode<int>(a);


    auto myList = MyList<std::pair<int, int>>();
    myList.Add({2,1});
    myList.Add({7,2});
    myList.Add({9,3});
    myList.Add({ 22, 4});
    myList.Add({2, 19});
    myList.Add({5, 6});
    auto listSize = myList.Size();
    auto listData = myList.GetData();
    auto beginIter = myList.begin();
    auto iter11 = beginIter++;
    auto iter12 = ++beginIter;
    auto f = iter12->first;
    auto s = iter12->second;
    return 0;
}
