#pragma once
#include <boost/format.hpp>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>

namespace file_split {
    struct block {
        std::size_t begin;
        std::size_t end;

    };
    
    std::vector<block> GetBlocksFromFile(const std::filesystem::path aPath, const std::size_t aParts);
    void SaveFilePart(std::ifstream& aFile, const file_split::block& aBlock, const std::size_t aCounter);
}
