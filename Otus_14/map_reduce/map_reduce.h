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
        if (m_MappedData.empty())
            return;//TODO::—ќќЅў≈Ќ»≈
        ShuffleAll();

        for (const auto& [data, mutex] : m_ReducedData) {
            //запускаем функтор
            int stop1 = 0;
        }
    }

private:
    std::size_t m_MapThreads = 1;
    std::size_t m_ReduceThreads = 1;
    boost::function<std::unique_ptr<IHasher<THash>>()> m_HasherFactory;
    std::mutex m_Mutex;
    std::list<hashs_t> m_MappedData;
    std::list<std::pair<hashs_t, std::mutex>> m_ReducedData;


    void MapBlock(std::unique_ptr<IHasher<THash>>&& aHasher, file_split::block aBlock, std::filesystem::path aFilePath) {
        if (!aHasher)
            return;

        Mapper<THash> mapper{ std::move(aHasher) };

        auto hashes = mapper.Calc(aFilePath, aBlock);
        std::lock_guard<decltype(m_Mutex)> locker(m_Mutex);
        m_MappedData.push_back(std::move(hashes));
    }

    void ShuffleAll() {
        std::vector<std::thread> threads;
        const std::size_t numberOfMapped = GetAllMappedSize();
        const std::size_t portionSize = GetAllMappedSize() / m_ReduceThreads;
        m_ReducedData.resize(m_ReduceThreads);
       
        for (auto& hashs : m_MappedData) {
            threads.push_back(std::thread(&MapReduce::ShuffleOne, this, std::move(hashs), portionSize));
            hashs.clear();
        }
        m_MappedData.clear();

        for (auto& thr : threads) {
            if (thr.joinable())
                thr.join();
        }

        //TODO:: ”ƒјЋ»“№ ЅЋќ 
        const std::size_t numberOfReduced = GetAllReducedSize();
        auto iter1 = m_ReducedData.rbegin()->first.rbegin();
        for (iter1; iter1 != m_ReducedData.rbegin()->first.rend(); ++iter1){
            auto str1 = *iter1;
        }
        int stop1 = 0;
    }

    std::size_t GetAllMappedSize() {
        std::size_t numberOfElements = 0;
        for (auto& hashs : m_MappedData) {
            numberOfElements += hashs.size();
        }
        return numberOfElements;
    }

    std::size_t GetAllReducedSize() {
        std::size_t numberOfElements = 0;
        for (auto& [data, mutex]: m_ReducedData) {
            numberOfElements += data.size();
        }
        return numberOfElements;
    }

    void ShuffleOne(hashs_t&& aHashs, const std::size_t aPortionSize) {
        while (!aHashs.empty()){
            for (auto iter = m_ReducedData.begin(); iter != m_ReducedData.end(); ) {
                auto& [reduced, vmutex] = *iter;
                std::lock_guard<decltype(vmutex)> locker(vmutex);
                std::size_t reducedSize = reduced.size();
                std::move(aHashs.begin(), aHashs.end(), std::back_inserter(reduced));
                aHashs.clear();
                std::inplace_merge(reduced.begin(), std::next(reduced.begin(), reducedSize), reduced.end());
                ++iter;
                if ( iter != m_ReducedData.end() && reduced.size() > aPortionSize) {
                    auto borderIter = FindFirstUniqueIter(reduced, aPortionSize);//TODO:: сделать замену на метод, провер€ющий на границе дубликаты
                    std::move(borderIter, reduced.end(), std::back_inserter(aHashs));
                    reduced.erase(borderIter, reduced.end());
                }
            }
        }
    }

    auto FindFirstUniqueIter(hashs_t& aHashs, const std::size_t aOffset) {
        auto iter = std::next(aHashs.begin(), aOffset);
        auto nextIter = iter + 1;
        while (nextIter != aHashs.end() && *iter == *nextIter) {
            ++iter;
            ++nextIter;
        }
        return iter;
    }
};
