#pragma once
#include "hash/ihash.h"
#include <boost/filesystem.hpp>     
#include <fstream>
#include <iostream>
#include <string>

struct FileHasher {
    boost::filesystem::path Path;
    std::unique_ptr<IHash> Hasher;
    std::ifstream File;
    std::string Hash;

    bool operator<(const FileHasher& aRhs) const {
        return Path.has_branch_path() < aRhs.Path.has_branch_path();
    }
};
