#pragma once
#include <boost/filesystem.hpp>     
#include <boost/format.hpp> 
namespace {
    //TODO:: загнать их в класс FileController ???
    struct FileFilter {
        const std::size_t MinSize;
        const std::string Mask;
    };

    struct Directorys {
        const std::vector<boost::filesystem::path> Dirs;
        const std::vector<boost::filesystem::path> Dropped;
        const std::size_t Lvl;
        Directorys(const std::vector<std::string>& aDirs, const std::vector<std::string>& aDropped, const std::size_t aLvl)
            : Lvl(aLvl), Dirs(std::move(ConvertToBoostObj(aDirs))), Dropped(std::move(ConvertToBoostObj(aDropped))) {}
    private:
        Directorys();

        std::vector<boost::filesystem::path> ConvertToBoostObj(const std::vector<std::string>& aIn) {
            std::vector<boost::filesystem::path> res;
            for (const auto& elem : aIn) {
                res.emplace_back(boost::filesystem::path{ elem });
            }
            return res;
        }
    };
}

//Класс обеспечивает удобный для наших задач доступ к файловой   системе
class FileController final {
public:
    FileController(const Directorys&& aDirs, const FileFilter&& aFilter) : _Filter(std::move(aFilter)), _Dirs(aDirs) {}

private:
    Directorys _Dirs;
    FileFilter _Filter;
    FileController() = default;
};
//--dir, D - директория сканирования (может быть несколько)
//--except, E - директория исключенная из сканирования (может быть несколько)
//--lvl, L - уровень сканирования (0 - только текущий каталог)
//--min, M - минимальный размер рассматриваемых файлов
//--mask,N - маски имени файлов, не регистрозависимые
//--block,S - размер блока
//--hash, H --алгоритм хэширования (реализуем crc32, md5, что нибудь ещё)