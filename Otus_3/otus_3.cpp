#include <iostream>
#include <vector>
#include <map>
#include "my_allocator.h"
//-----------------------------------------------------------------------------
void TestAllocator()
{
    auto m = std::map<short, long long, std::less<int>, MapAllocator<std::pair<const short, long long>>>();
    int i = 0;
    for (; i < 10; ++i) {
        m[i] = 11 * i;
        //std::cout << std::endl;
    }
    auto& test = m._Getal();
}
//-----------------------------------------------------------------------------
int main(int, char *[])
{
    for (int i = 0; i < 5000000; ++i)
        TestAllocator();
    return 0;
}
