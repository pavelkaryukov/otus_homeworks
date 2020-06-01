#pragma once
template<class Res>
class IHasher {
public:
    virtual Res CalcHash(const void* aPtr, const std::size_t aSize, const std::size_t aPrefixSize) = 0;
private:
};