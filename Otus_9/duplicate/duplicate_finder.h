#pragma once
#include "hash/ihash.h"
#include "file/file_hash.h"
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>
#include <cctype>
#include <string>             
#include <map>      
#include <set>      
#include <unordered_map>                                                                          
#include <unordered_set>
struct FileDescr {
    std::string Hash;
    std::size_t Size;

    bool operator<(const FileDescr& aRhs) const {
        return std::tie(Hash, Size) < std::tie(aRhs.Hash, aRhs.Size);
    }
};

class DuplicateFinder{
    using duplicates_t = std::map<FileDescr, std::set<boost::filesystem::path>>;
    using files_t = std::unordered_map<std::uint64_t, std::set<FileHasher>>;
public:
    DuplicateFinder(boost::function<std::unique_ptr<IHash>()>&& aHashFactory) : _HashFactory(std::move(aHashFactory)) {}

    duplicates_t GetDuplicated(files_t& aFiles) {
        return {};
    }

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
