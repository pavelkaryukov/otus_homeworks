#pragma once
#include "hash/ihash.h"
#include <boost/filesystem.hpp>     
#include <fstream>
#include <iostream>

//Структура используется для подсчета Hash суммы файла
struct FileHasher {
    boost::filesystem::path Path;
    std::unique_ptr<IHash> Hash;
    std::ifstream File;
    std::size_t Processed = 0;

    bool operator<(const FileHasher& aRhs) const {
        return Path.has_branch_path() < aRhs.Path.has_branch_path();
    }
};
//