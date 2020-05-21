#pragma once
#include <boost/filesystem.hpp>     
#include <string>
#include <set>
#include <vector>
///\brief структура хранит в себе пути к каталогам, пути к каталогам, которые исключены и поиска дубликатов, глубину вхождения
struct DirBorder {
    
    ///\brief каталоги, где осуществляется поиск дубликатов
    const std::set<boost::filesystem::path> Dirs;
    ///\brief каталоги где не нужно осуществлять поиск дубликатов
    const std::set<boost::filesystem::path> Dropped;
    ///\brief глубина поиска - 0 только текущий каталог
    const std::size_t Lvl = 0;

    DirBorder(const std::vector<std::string>& aDirs, const std::vector<std::string>& aDropped, const std::size_t aLvl)
        : Lvl(aLvl), Dirs(std::move(ConvertToBoostObj(aDirs))), Dropped(std::move(ConvertToBoostObj(aDropped))) {}
private:
    DirBorder() = default;

    std::set<boost::filesystem::path> ConvertToBoostObj(const std::vector<std::string>& aIn) {
        std::set<boost::filesystem::path> res;
        for (const auto& elem : aIn) {
            res.insert(boost::filesystem::path{ elem });
        }
        return res;
    }
};
