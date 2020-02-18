#include <iostream>
#include <vector>
#include <map>
#include "my_allocator.h"
#include "factorial.h"
//-----------------------------------------------------------------------------
void TestAllocatorMap()
{
    using mkey = std::size_t;
    using mvalue = std::size_t;

    auto m = std::map<mkey, mvalue, std::less<mkey>, MapAllocator<std::pair<const mkey, mvalue>, 10>>();
    int i = 0;
    
    for (; i < 11; ++i) {
        auto myAlloc = m._Getal();
        m[i] = i * 10;
        std::cout << m[i] << std::endl;
    }
    //auto myAlloc = m._Getal();
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
   
    std::cout << "Start Program" << std::endl;
    //TestAllocatorMap();
    //TestAllocatorVector();
    std::cout << "Close Program" << std::endl;
    return 0;
}

