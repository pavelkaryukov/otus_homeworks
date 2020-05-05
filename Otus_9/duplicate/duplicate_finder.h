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
    using files_t = std::unordered_map<std::uint64_t, std::set<boost::filesystem::path>>;
public:
    DuplicateFinder(boost::function<std::unique_ptr<IHash>()>&& aHashFactory, const std::size_t aBuffSize) : _HashFactory(std::move(aHashFactory)) {
        _Buffer.resize(aBuffSize);
    }

    duplicates_t GetDuplicated(const files_t& aFiles) {
        std::vector<FileHasher> vect;
        for (auto&[size, hasherSet] : aFiles) {
            for (auto&[size, files] : aFiles) {
                if (files.size() <= 2)
                    continue;
                for (auto& file : files) {
                    vect.push_back({ file });
                }
                DuplicateCalc(vect);
                vect.clear();
            }
        }
        return {};
    }

    std::string TestHash() {
        auto _hash = _HashFactory();
        _hash->ProcessBuffer(_testStr.data(), _testStr.size());
        return _hash->Result();
    }
private:
    const std::string _testStr = "my test string, ahahhahahahsrasr";
    std::vector<std::uint8_t> _Buffer;
    boost::function<std::unique_ptr<IHash>()> _HashFactory;
    DuplicateFinder() = default;

    void DuplicateCalc(std::vector<FileHasher>& aFiles) {
        if (aFiles.empty())
            return;
        for (auto& file : aFiles) {
            if (!file.Hash) {
                file.Hash = (_HashFactory());
            }
            if (!file.File.is_open()) {
                file.File.open(file.Path.string(), std::fstream::binary);
            }
        }
        int stop1 = 0;
    }
};
