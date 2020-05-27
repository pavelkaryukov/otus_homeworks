#pragma once                
#include "mapper/hasher/ihasher.h"
#include <boost/crc.hpp>
#include <cstddef>

class HasherCRC : public IHasher<std::size_t> {
public:
    std::size_t CalcHash(const void* aPtr, const std::size_t aSize) override {
        m_�rc32.process_bytes(aPtr, aSize);
        auto res = m_�rc32.checksum();
        m_�rc32.reset();
        return res;
    }
private:
    boost::crc_32_type  m_�rc32;
};