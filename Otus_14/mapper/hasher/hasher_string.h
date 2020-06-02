#pragma once
#include "mapper/hasher/ihasher.h"
#include <string> 

class HasherString : public IHasher<std::string> {
public:
    std::string CalcHash(const void* aPtr, const std::size_t aSize, const std::size_t aPrefixSize) override {
        const std::size_t len = (aPrefixSize != 0) ? std::min(aPrefixSize, aSize) : aSize;
        return std::string((char*)aPtr, (char*)aPtr + len);
    }
private:
};
