#pragma once
#include <boost/filesystem.hpp>     
#include <boost/format.hpp> 
#include <vector>//TODO:: переделать hash set
#include <set>//TODO:: переделать hash set

//TODO::Не забыть покрыть все try_cath
namespace {
    //TODO:: загнать их в класс FileController ???
    class FileFilter {
    public:
        const std::size_t MinSize = 0;
        const std::string Mask = "*";

        FileFilter(const std::size_t aMinSize, const std::string&  aMask) : MinSize(aMinSize), Mask(aMask) {
            
        }


        bool IsPermittedSize(const boost::filesystem::directory_entry& aObj) const {
            return  (MinSize == 0) || (boost::filesystem::file_size(aObj) >= MinSize);
        }

        bool IsPermittedMask(const boost::filesystem::directory_entry& aObj) const {
            return true;
        }

    private:
        FileFilter() = default;
    };

    struct Directorys {
        const std::set<boost::filesystem::path> Dirs;
        const std::set<boost::filesystem::path> Dropped;
        const std::size_t Lvl = 0;
        Directorys(const std::vector<std::string>& aDirs, const std::vector<std::string>& aDropped, const std::size_t aLvl)
            : Lvl(aLvl), Dirs(std::move(ConvertToBoostObj(aDirs))), Dropped(std::move(ConvertToBoostObj(aDropped))) {}
    private:
        Directorys();

        std::set<boost::filesystem::path> ConvertToBoostObj(const std::vector<std::string>& aIn) {
            std::set<boost::filesystem::path> res;
            for (const auto& elem : aIn) {
                res.insert(boost::filesystem::path{ elem });
            }
            return res;
        }
    };
}

//Класс обеспечивает удобный для наших задач доступ к файловой   системе
class FileController final {
    using files_t = std::vector<boost::filesystem::path>;
public:
    FileController(const Directorys&& aDirs, const FileFilter&& aFilter) : _Filter(std::move(aFilter)), _Dirs(aDirs) {
        FillFiles();
    }

private:
    Directorys _Dirs;
    FileFilter _Filter;
    FileController() = default;
    files_t _Files;

    void FillFiles() {
        files_t allFiles;
        for (const auto& dir : _Dirs.Dirs) {
            FillFiles(dir, 0, allFiles);//Начинаем с 1, т.к. 0
        }
        _Files = std::move(allFiles);
    }

    void FillFiles(const boost::filesystem::path& aDir, const std::size_t aLvl, files_t& aFiles) {
        if (_Dirs.Lvl != 0 && aLvl >= _Dirs.Lvl)
            return;
        if (_Dirs.Dropped.find(aDir) != _Dirs.Dropped.end())
            return;

        if (!boost::filesystem::exists(aDir) || !boost::filesystem::is_directory(aDir)) {
            std::cout << boost::format("Каталог [%1%] не существует") % aDir << std::endl;
            return;
        }

        for (auto& obj : boost::filesystem::directory_iterator(aDir)) {
            if (boost::filesystem::is_directory(obj)) {
                FillFiles(obj, aLvl + 1, aFiles);
                continue;
            }
            if (boost::filesystem::is_regular_file(obj)) {
                if (!_Filter.IsPermittedSize(obj)) {
                    continue;
                }
                if (!_Filter.IsPermittedMask(obj)) {
                    continue;
                }
                aFiles.push_back(obj);
            }
        }
    }
};
//--dir, D - директория сканирования (может быть несколько)
//--except, E - директория исключенная из сканирования (может быть несколько)
//--lvl, L - уровень сканирования (0 - только текущий каталог)
//--min, M - минимальный размер рассматриваемых файлов
//--mask,N - маски имени файлов, не регистрозависимые
//--block,S - размер блока
//--hash, H --алгоритм хэширования (реализуем crc32, md5, что нибудь ещё)