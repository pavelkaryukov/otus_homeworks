#include "otus.h"
//-----------------------------------------------------------------------------
int main(int, char *[])
{    
   
    otus::StandardMap mapStandartAllocator;
    otus::CustomMap mapCustomAllocator;
    otus::FillMap(mapStandartAllocator);
    otus::FillMap(mapCustomAllocator);
    for (auto& [key, value] : mapCustomAllocator) {
        std::cout << key << " " << value << std::endl;
    }
    otus::StandardMyList myListStandartAllocator;
    otus::CustomMyList   myListCustomAllocator;
    otus::FillMyList(myListStandartAllocator);
    otus::FillMyList(myListCustomAllocator);
    for (auto& elem : myListCustomAllocator) {
        std::cout << elem << std::endl;
    }
    return 0;
}
