#include <iostream>
#include <vector>
#include <map>
#include "my_allocator.h"
//-----------------------------------------------------------------------------
int main(int, char *[])
{
    auto m = std::map<short, long long, std::less<int>, MapAllocator<std::pair<const short, long long>>>{};
    int i = 0;
    for (; i < 10; ++i) {
        m[i] = 11*i;
        std::cout << std::endl;
    }
    auto& test = m._Getal();
    return 0;
}
