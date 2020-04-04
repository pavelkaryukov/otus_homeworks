#include "otus.h"
//-----------------------------------------------------------------------------
int main(int, char *[])
{    
   
    //std::list<int> test;

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
//    std::cout << "MyList with Standart  Allocator\r\n";
//    for (auto& elem : myListStandartAllocator) {
//        std::cout << elem << std::endl;
//    }
//    std::cout << "MyList with  MyAllocator\r\n";
    for (auto& elem : myListCustomAllocator) {
        std::cout << elem << std::endl;
    }
    return 0;
}
