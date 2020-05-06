#pragma once
#include "hash/ihash.h"
#include "file/file_hash.h"
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>
#include <cctype>          
#include <map>      
#include <set>   
#include <string>   
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
    using hash_sum_t = std::string;
    using hashs_t = std::unordered_map<hash_sum_t, std::size_t>;
    using files_t = std::unordered_map<std::uint64_t, std::set<boost::filesystem::path>>;
public:
    DuplicateFinder(boost::function<std::unique_ptr<IHash>()>&& aHashFactory, const std::size_t aBuffSize) : 
        _hasherFactory(std::move(aHashFactory)), _blockSize(aBuffSize != 0 ? aBuffSize : 1024) {
        _buffer.resize(aBuffSize);
    }

    void OutputDuplicated(const files_t& aFiles, const bool aFullPaths) {
        std::vector<FileHasher> vect;
        for (auto&[size, hasherSet] : aFiles) {
            if (hasherSet.size() <= 1)
                continue;
            for (auto& filename : hasherSet){ 
                vect.push_back({ filename });
            }
        }
        DuplicateCalc(vect, aFullPaths);
        vect.clear();
    }

private:
    std::vector<char> _buffer;
    const std::size_t _blockSize = 1024;
    boost::function<std::unique_ptr<IHash>()> _hasherFactory;
    DuplicateFinder() = default;

    void DuplicateCalc(std::vector<FileHasher>& aFiles, const bool aFullPaths) {
        InitFilesHasher(aFiles);
        const std::uintmax_t kFileSize = boost::filesystem::file_size(aFiles[0].Path);
        std::uintmax_t processed = 0;
        hashs_t hashs;
        while (processed < kFileSize && aFiles.size() >= 1) {
            hashs = MakeHashIteration(aFiles, processed);// переделать на unordered map ???
            EraseUniaqueFiles(aFiles, hashs);           
        }

        if (!aFiles.empty()) {
            OtputDuplicateFileNames(hashs, aFiles, aFullPaths);
        }
    }

    hashs_t MakeHashIteration(std::vector<FileHasher>& aFiles, std::uintmax_t& aProcessed) {
        hashs_t hashSums;
        for (auto iter = aFiles.begin(); iter != aFiles.end();) {
            if (!iter->Hasher || !iter->File.is_open()) {
                iter = aFiles.erase(iter);
                continue;
            }
            _buffer.clear();
            _buffer.resize(_blockSize);
            iter->File.read(_buffer.data(), _buffer.size());
            iter->Hasher->ProcessBuffer(_buffer.data(), _buffer.size());
            iter->Hash = iter->Hasher->Result();
            hashSums[iter->Hash] += 1;
            ++iter;
        }
        aProcessed += _blockSize;
        return hashSums;
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
                iter->Hasher = _hasherFactory();

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

    void OtputDuplicateFileNames(const hashs_t&  aHashs, const std::vector<FileHasher>& aFiles, const bool aFullPaths) {
        for (auto&[hash, number] : aHashs) {
            if (number <= 1)
                continue;
            for (auto& fileHasher : aFiles) {
                if (hash != fileHasher.Hash) 
                    continue;

                if (aFullPaths) 
                    std::cout << fileHasher.Path << std::endl;
                else 
                    std::cout << fileHasher.Path.filename() << std::endl;
            }
            std::cout << std::endl;
        }
    }
};
