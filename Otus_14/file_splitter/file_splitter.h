#pragma once
#include <boost/format.hpp>
#include <filesystem>
#include <fstream>
#include <vector>
//TODO:: заполнить сообщения об ошибках при генерации исключений

namespace file_split {
    struct block {
        std::size_t begin;
        std::size_t end;

    };
    
    std::vector<block> GetBlocksFromFile(const std::filesystem::path aPath, const std::size_t aParts);
    void SaveFilePart(std::ifstream& aFile, const file_split::block& aBlock, const std::size_t aCounter);
}

//class FileSplitter {
//    FileSplitter(const std::filesystem::path aFilePath, const std::size_t aParts) : m_Parts(aParts < 0 ? 1 : aParts) {
//        if (!std::filesystem::exists(aFilePath)) {
//            m_Valid = false;
//            return;
//        }
//        m_File.open(aFilePath);
//        if (!m_File.is_open()){
//            m_Valid = false;
//            return;
//        }
//
//    }
//public:
//private:
//    bool m_Valid= true;
//    std::ifstream m_File;
//    const std::size_t m_Parts = 1;
//};
