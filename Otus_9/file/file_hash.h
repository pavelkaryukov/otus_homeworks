#pragma once
#include "hash/ihash.h"
#include <boost/filesystem.hpp>     
#include <fstream>
#include <iostream>
#include <string>
/**
* \brief  ����� ������ �������  ��������� ��������� ����� (����, ��� �����, �������� �����������).
*/
struct FileHasher {
    ///\brief  ���� � �����
    boost::filesystem::path Path;
    ///\brief  ������ ������ ����������� �������� ����������� (��������� IHash)
    std::unique_ptr<IHash> Hasher;
    ///\brief  ����� std::ifstream ��� ������� � �����
    std::ifstream File;

    bool operator<(const FileHasher& aRhs) const {
        return Path.has_branch_path() < aRhs.Path.has_branch_path();
    }
};
