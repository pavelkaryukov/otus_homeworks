#pragma once
#include "hash/ihash.h"
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>
#include <cctype>
#include <string>

class DuplicateFinder{
public:
    DuplicateFinder(boost::function<std::unique_ptr<IHash>()>&& aHashFactory) : _HashFactory(std::move(aHashFactory)) {}
    
    std::string TestHash() {
        auto _hash = _HashFactory();
        _hash->ProcessBuffer(_testStr.data(), _testStr.size());
        return _hash->Result();
    }

private:
    const std::string _testStr = "my test string, ahahhahahahsrasr";
    boost::function<std::unique_ptr<IHash>()> _HashFactory;
    DuplicateFinder() = default;
};
