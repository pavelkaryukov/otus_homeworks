#pragma once
#include "hash/ihash.h"
#include <boost/filesystem.hpp>     
#include <fstream>
#include <iostream>
#include <string>
/**
* \brief  класс хранит текущее  состояние обработки файла (путь, хэш сумму, алгоритм хэширофания).
*/
struct FileHasher {
    ///\brief  Путь к файлу
    boost::filesystem::path Path;
    ///\brief  объект класса реализующий алгоритм хэширования (интерфейс IHash)
    std::unique_ptr<IHash> Hasher;
    ///\brief  поток std::ifstream для доступа к файлу
    std::ifstream File;

    bool operator<(const FileHasher& aRhs) const {
        return Path.has_branch_path() < aRhs.Path.has_branch_path();
    }
};
