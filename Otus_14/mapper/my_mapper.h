#pragma once
#include "mapper/hasher/ihasher.h"
#include <memory>
#include <vector>

template<class THash>
class Mapper {
public:
    Mapper(std::unique_ptr<IHasher<THash>>&& aMapper) : m_Hasher(std::move(aMapper)) {
    }
    
    std::vector<THash> Calc(const std::vector<std::string>& aStrs) {
        if (!m_Hasher)
            return {};

        std::vector<THash> res;
        for (const auto& str : aStrs) {
            res.emplace_back(m_Hasher->CalcHash(str.data(), str.size()));
        }
        return res;
    }

private:
    Mapper() = default;
    std::unique_ptr<IHasher<THash>> m_Hasher;
};