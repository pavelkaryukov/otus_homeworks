#pragma once
#include <boost/filesystem.hpp>     
#include "hash/ihash.h"
//��������� ������������ ��� �������� Hash ����� �����
struct FileHasher {
    boost::filesystem::path Path;
    std::unique_ptr<IHash> Hash;
    FILE* File = nullptr;
    std::size_t Processed = 0;

    bool operator<(const FileHasher& aRhs) const {
        return Path < aRhs.Path;
    }
};
