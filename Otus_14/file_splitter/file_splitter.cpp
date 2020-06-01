#include "file_splitter/file_splitter.h"

namespace file_split {

    std::size_t NewLineStartPos(std::ifstream& aFile, const std::size_t aStartPos, const std::size_t aFileSize) {
        if (!aFile.is_open())
            throw std::logic_error("");
        auto pos = aStartPos;
        aFile.seekg(pos);
        const std::size_t buffSize = 256;
        char buff[buffSize] = { 0 };
        const std::size_t len = std::min(aFileSize - aStartPos, buffSize);

        while (aFile.read(buff, len)) {
            if (!aFile)
                return aFileSize;

            for (auto i = 0U; i < len; ++i) {
                if (buff[i] == '\n') {
                    pos += i;
                    return pos;
                }
            }
            pos += len;
        }

    }
    
    std::vector<block> GetBlocksFromFile(const std::filesystem::path aPath, const std::size_t aParts) {
        if (aParts < 1)
            throw std::logic_error("");

        if (!std::filesystem::exists(aPath))
            throw std::logic_error("");

        std::ifstream file{ aPath };
        if (!file.is_open())
            throw std::logic_error("");

        const std::size_t fileSize = std::filesystem::file_size(aPath);
        if (fileSize == 0)
            throw std::logic_error("");

        const std::size_t expectedBlockSize = fileSize / aParts;
        std::vector<block> blocks;
        std::size_t pos = 0;

        while (pos < fileSize) {
            if (pos  + expectedBlockSize >= fileSize) {
                blocks.push_back({ pos,  fileSize });
                break;
            }

            std::size_t startPos = pos;
            std::size_t endPos = NewLineStartPos(file, pos + expectedBlockSize, fileSize) + 1;
            blocks.push_back({ pos,  endPos });
            pos += (endPos - pos);
        }
        return blocks;
    }

    void SaveFilePart(std::ifstream& aFile, const file_split::block& aBlock, const std::size_t aCounter) {
        std::ofstream filePart(boost::str(boost::format("file_part_%1%") % aCounter), std::ios::binary);

        if (!filePart || !filePart.is_open())
            throw std::logic_error("");
        aFile.seekg(aBlock.begin);
        if (!aFile)
            throw std::logic_error("");

        std::size_t pos = aBlock.begin;
        std::vector<char> data;
        const std::size_t buffSize = std::min(aBlock.end - aBlock.begin, 256U * 1024U);//256 кб хватит всем
        data.resize(buffSize);

        while (aFile && aFile.tellg() < aBlock.end) {
            if (data.size() == 0)
                throw std::logic_error("");
            std::size_t currPos = aFile.tellg();
            std::size_t len = std::min(buffSize, aBlock.end - currPos);
            aFile.read(data.data(), len);
            const auto readed = aFile ? len : aFile.gcount();
            filePart.write(data.data(), readed);
        }
    }
}