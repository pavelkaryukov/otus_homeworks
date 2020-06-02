#pragma once
#include "mapper/hasher/ihasher.h"
#include "file_splitter/file_splitter.h"
#include <algorithm>
#include <memory>
#include <vector>

template<class THash>
class Mapper {
public:
    Mapper(std::unique_ptr<IHasher<THash>>&& aMapper, const std::size_t aPrefixSize) : m_Hasher(std::move(aMapper)), m_PrefixSize(aPrefixSize) {
    }
    
    std::vector<THash> Calc(const std::vector<std::string>& aStrs) {
        if (!m_Hasher) 
            throw std::logic_error("m_Hasher не инициализирован");
        
        std::vector<THash> res;
        for (const auto& str : aStrs) {
            res.emplace_back(m_Hasher->CalcHash(str.data(), str.size()));
        }
        return res;
    }

    std::vector<THash> Calc(std::filesystem::path& aPath, const file_split::block& aBlock) {
        if (aBlock.begin > aBlock.end)
            throw std::logic_error(boost::str(boost::format("Конец блока [%1%] меньше начала [%2%]") % aBlock.end % aBlock.begin));
        if (!m_Hasher)
            throw std::logic_error("m_Hasher не инициализирован");

        std::ifstream file(aPath/*, std::ios::binary*/);
        if (!file || !file.is_open())
            throw std::logic_error(boost::str(boost::format("файл с именем [%1%] не удается открыть")%aPath));
        
        const std::size_t fileSize = std::filesystem::file_size(aPath);
        if (fileSize <= aBlock.begin)
            throw std::logic_error(boost::str(boost::format("Размер файла [%1%] <= начала блока[%2%]") % fileSize % aBlock.begin));

        file.seekg(aBlock.begin);

        std::vector<THash> res;
        std::string str;
        while (std::getline(file, str)) {
            std::size_t pos = file.tellg();
            auto hash = m_Hasher->CalcHash(str.data(), str.size(), m_PrefixSize);
            res.insert(std::upper_bound(res.begin(), res.end(), hash), hash);
            if (pos >= fileSize || pos >= aBlock.end)
                break;
        }
        return res;
    }
private:
    Mapper() = default;
    std::unique_ptr<IHasher<THash>> m_Hasher;
    const std::size_t m_PrefixSize = 0;
};