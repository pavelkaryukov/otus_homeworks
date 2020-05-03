#pragma once
#include "hash/ihash.h"
#include <boost/uuid/detail/md5.hpp>
#include <boost/format.hpp>
class HashMD5 : public iHash {
public:
    void ProcessBuffer(const void* aData, const std::size_t aLen) override {
        _hash.process_bytes(aData, aLen);
    }

    const std::string Result() override {
        _hash.get_digest(_digest);
        std::string res;
        for (auto& elem : digest) {
            res += boost::str(boost::format("[%1%]") % elem);
        }
    }
private:
    boost::uuids::detail::md5 _hash;
    boost::uuids::detail::md5::digest_type _digest;
};

