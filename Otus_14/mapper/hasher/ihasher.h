#pragma once
template<class Res>
class IHasher {
public:
    virtual Res CalcHash(const void* aPtr, const std::size_t aSize) = 0;
private:
};