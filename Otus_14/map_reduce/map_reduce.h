#pragma once
#include "mapper/hasher/ihasher.h"
#include "mapper/my_mapper.h"
#include "file_splitter/file_splitter.h"
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <list>    
#include <limits>

template<class THash>
class MapReduce {
    using hashs_t = std::vector<THash>;
public:
    MapReduce(
        boost::function<std::unique_ptr<IHasher<THash>>()>&& aHasherFactory,
        const std::size_t aMapThr,
        const std::size_t aRedThr
    ) : m_HasherFactory(std::move(aHasherFactory)), 
        m_MapThreads(aMapThr <= 0 ? 1 : aMapThr), 
        m_ReduceThreads(aRedThr <= 0 ? 1 : aRedThr) {
    }

    void Process(std::filesystem::path aFilePath) {
        if (!std::filesystem::exists(aFilePath)) {
            std::cout << boost::format("File=[%1%] not exist") % aFilePath << std::endl;
            return;
        }
        auto blocks = file_split::GetBlocksFromFile(aFilePath, m_MapThreads);
        std::vector<std::thread> threads;
        for (const auto& block : blocks) {
            threads.push_back(std::thread(&MapReduce::MapBlock, this, m_HasherFactory(), block, aFilePath));
        }
        for (auto& thr : threads) {
            if (thr.joinable())
                thr.join();
        }
        threads.clear();
        if (m_MappedHashs.empty())
            return;//TODO::—ŒŒ¡Ÿ≈Õ»≈
        ShuffleAll();
    }

private:
    std::size_t m_MapThreads = 1;
    std::size_t m_ReduceThreads = 1;
    boost::function<std::unique_ptr<IHasher<THash>>()> m_HasherFactory;
    std::mutex m_Mutex;
    std::list<hashs_t> m_MappedHashs;
    std::list<std::pair<hashs_t, std::mutex>> m_ReduceData;


    void MapBlock(std::unique_ptr<IHasher<THash>>&& aHasher, file_split::block aBlock, std::filesystem::path aFilePath) {
        if (!aHasher)
            return;

        Mapper<THash> mapper{ std::move(aHasher) };

        auto hashes = mapper.Calc(aFilePath, aBlock);
        std::lock_guard<decltype(m_Mutex)> locker(m_Mutex);
        m_MappedHashs.push_back(std::move(hashes));

//         const std::size_t blockSize = hashes.size() / m_MappedHashs.size();
    }

    void ShuffleAll() {
        std::vector<std::thread> threads;
        for (auto& hashs : m_MappedHashs) {
            threads.push_back(std::thread(&MapReduce::ShuffleOne, this, std::move(hashs)));
        }

        for (auto& thr : threads) {
            if (thr.joinable())
                thr.join();
        }
    }

    void ShuffleOne(hashs_t&& aHashs) {
        const std::size_t portionSize = aHashs.size() / m_ReduceThreads;
        while (!hashes.empty()){
            auto minIter = m_ReduceData.begin();
            std::size_t minSize = std::numeric_limits<std::size_t>::max();
            for (auto iter = m_ReduceData.begin(); iter != m_ReduceData.end(); ++iter) {
                auto& [vect, vmutex] = *iter;
                std::lock_guard<decltype(vmutex)> locker(vmutex);
                if (vect.size() < minSize){
                    minSize = vect.size();
                    minIter = iter;
                }
            }


        }
    }
};
