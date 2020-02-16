#include <iostream>
#include <vector>
#include <map>
#include "my_allocator.h"
//-----------------------------------------------------------------------------
void TestAllocator()
{
    auto m = std::map<short, long long, std::less<int>, MapAllocator<std::pair<const short, long long>>>();
    std::cout << "Map Test" << std::endl;
    for (int i = 0; i < 10; ++i) {
        m[i] = 11 * i;
        std::cout << m[i] << std::endl;
        //std::cout << std::endl;
    }

    auto v = std::vector<short, MapAllocator<short>>();    
    std::cout << "Vector Test" << std::endl;
    for (int i = 0; i < 10; ++i) {
        v.emplace_back(11*i);
        std::cout << v[i]<< std::endl;
    }
}
//-----------------------------------------------------------------------------
int main(int, char *[])
{
    std::cout << "Start Program" << std::endl;
    TestAllocator();
// 
//     long long count=0;
//     for (int i = 0; i < 5000000; ++i) {
//         TestAllocator();
//         ++count;
//         if (count % 10000) {
//             std::cout << count << std::endl;
//         }
//     }
    std::cout << "Close Program" << std::endl;
    return 0;
}
