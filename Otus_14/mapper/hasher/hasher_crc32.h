#pragma once                
#include "mapper/hasher/ihasher.h"
#include <boost/crc.hpp>
#include <cstddef>

class HasherCRC : public IHasher<std::size_t> {
public:
    std::size_t CalcHash(const void* aPtr, const std::size_t aSize, const std::size_t aPrefixSize) override {
        const std::size_t len = (aPrefixSize != 0) ? std::min(aPrefixSize, aSize) : aSize;
        m_crc32.process_bytes(aPtr, len);
        auto res = m_crc32.checksum();
        m_crc32.reset();
        return res;
    }
private:
    boost::crc_32_type  m_crc32;
};