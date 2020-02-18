#include <iostream>
#include <vector>
#include <map>
#include "my_allocator.h"
//-----------------------------------------------------------------------------
void TestAllocator()
{
    auto m = std::map<short, long long, std::less<int>, MapAllocator<std::pair<const short, long long>>>();
    int i = 0;
    for (; i < 40; ++i) {
        m[i] = 11 * i;
        //std::cout << m[i] << std::endl;
    }
}
//-----------------------------------------------------------------------------
 int main(int, char *[])
 {
     std::cout << "Start Program" << std::endl;
     long long count=0;
     for (int i = 0; i < 5000000; ++i) {
         TestAllocator();
         ++count;
         if ((count % 10000)==0) {
             std::cout << count << std::endl;
         }
     }
     std::cout << "Close Program" << std::endl;
     return 0;
 }

//-----------------------------------------------------------------------------
//int main(int, char *[])
//{
//    std::cout << "Start Program" << std::endl;
//    TestAllocator();
//    std::cout << "Close Program" << std::endl;
//    return 0;
//}

