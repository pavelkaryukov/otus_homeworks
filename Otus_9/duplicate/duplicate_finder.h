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
    using hashs_t = std::unordered_map<std::string, std::size_t>;
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

private:
    std::vector<std::uint8_t> _Buffer;
    boost::function<std::unique_ptr<IHash>()> _HashFactory;
    DuplicateFinder() = default;

    void DuplicateCalc(std::vector<FileHasher>& aFiles) {
        InitFilesHasher(aFiles);
        const std::size_t kFileSize = boost::filesystem::file_size(aFiles[0].Path);
        std::size_t processed = 0;
        hashs_t hashs;
        while (processed < kFileSize && aFiles.size() >= 1) {
            hashs = MakeHashIteration(aFiles, processed);// переделать на unordered map ???
            EraseUniaqueFiles(aFiles, hashs);           
        }

        if (!aFiles.empty()) {
            //TODO::вывод
        }
    }

    hashs_t MakeHashIteration(std::vector<FileHasher>& aFiles, std::size_t& aProcessed) {

        return {};
    }

    void EraseUniaqueFiles(std::vector<FileHasher>& aFiles, const hashs_t& aHashs) {
        for (auto iter = aFiles.begin(); iter != aFiles.end();) {            
            auto hashIter = aHashs.find(iter->Hash);
            if (hashIter == aHashs.end()) {
                ++iter;
                continue;
            }

            const auto& [hash, size] = *hashIter;
            if (size <= 1) {
                iter = aFiles.erase(iter);
                continue;
            }
            ++iter;
        }
    }

    void InitFilesHasher(std::vector<FileHasher>& aFiles) {
        if (aFiles.empty())
            return;
        for (auto iter = aFiles.begin(); iter != aFiles.end();) {
            if (!iter->Hasher) {
                iter->Hasher = _HashFactory();

                if (!iter->File.is_open()) {
                    iter->File.open(iter->Path.string(), std::fstream::binary);
                    if (!iter->File.is_open()) {
                        iter = aFiles.erase(iter);
                        continue;
                    }
                }
            }
            ++iter;
        }
    }

};
