#pragma once
#include "mapper/my_mapper.h" 
#include "mapper/hasher/hasher_crc32.h"
#include "mapper/hasher/hasher_string.h"
#include "file_splitter/file_splitter.h"
#include "map_reduce/map_reduce.h"
#include "reducer/reducer.h"

std::size_t GetPrefixSize(std::filesystem::path aPath, const std::size_t aMapThreads, const std::size_t aReducerThreads) {
    if (!std::filesystem::exists(aPath)) {
        std::cout << boost::format("Файл с именем [%1%] не существует") % aPath << std::endl;
        return 0;
    }
    using hash_t = std::string;
    using hashFactory_t = boost::factory<std::unique_ptr<HasherString>>;
    MapReduce<hash_t> mapReducer{ hashFactory_t(), aMapThreads,  aReducerThreads, ReduceFunc<hash_t> };
    const std::size_t uniqueHashs = mapReducer.Process(aPath, 0);
    std::size_t prefixSize = 0;
    std::size_t uniqueHashsWithPrefix = 0;
    
    while (uniqueHashsWithPrefix!= uniqueHashs) {
        uniqueHashsWithPrefix = mapReducer.Process(aPath, ++prefixSize);
    }
    return prefixSize;
}
