#pragma once
#include "mapper/hasher/ihasher.h"
#include <string> 
class HasherString : public IHasher<std::string> {
public:
    std::string CalcHash(const void* aPtr, const std::size_t aSize) override {
        return std::string((char*)aPtr, (char*)aPtr + aSize);
    }
private:
};
