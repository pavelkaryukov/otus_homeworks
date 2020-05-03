#pragma once
#include "hash/ihash.h"
#include <boost/crc.hpp>
#include <boost/format.hpp>
class HashMD5 : public iHash {
public:
    void ProcessBuffer(const void* aData, const std::size_t aLen) override {        
        _result.process_bytes(aData, aLen);
    }

    const std::string Result() override {
        return std::to_string(_result.checksum())
    }
private:
    boost::crc_32_type  _result;
};



