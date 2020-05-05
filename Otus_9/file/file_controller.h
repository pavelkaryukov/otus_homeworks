#pragma once
#include <boost/filesystem.hpp>     
#include <boost/format.hpp> 
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <vector>
#include <unordered_map> 
#include <set>//TODO:: переделать hash set
namespace Border {
    class FileBorder {
    public:
        FileBorder(const std::size_t aMinSize, const std::string&  aMask) : _MinSize(aMinSize), _Filter(MaskToRegex(aMask)) {
            
        }

        bool IsPermittedSize(const boost::filesystem::directory_entry& aObj) const {
            return  (_MinSize == 0) || (boost::filesystem::file_size(aObj) >= _MinSize);
        }

        bool IsPermittedMask(const boost::filesystem::directory_entry& aObj) const {            
            if (_Filter.str() == "*" || _Filter.str() == "")
                return true;
            std::string filename = aObj.path().filename().string();
            std::transform(filename.begin(), filename.end(), filename.begin(), [](unsigned char c) { return std::tolower(c); });
            boost::smatch what;
            return boost::regex_match(filename, what, _Filter);
        }
    private:
        FileBorder() = default;
        const std::size_t  _MinSize = 0;
        const boost::regex _Filter { "" };
       
        std::string MaskToRegex(std::string aStr) {
            std::transform(aStr.begin(), aStr.end(), aStr.begin(), [](unsigned char c) { return std::tolower(c); });            
            boost::replace_all(aStr, ".", "\.");
            boost::replace_all(aStr, "*", ".*");
            return aStr;
        }
    };

    struct Directorys {
        const std::set<boost::filesystem::path> Dirs;
        const std::set<boost::filesystem::path> Dropped;
        const std::size_t Lvl = 0;
        Directorys(const std::vector<std::string>& aDirs, const std::vector<std::string>& aDropped, const std::size_t aLvl)
            : Lvl(aLvl), Dirs(std::move(ConvertToBoostObj(aDirs))), Dropped(std::move(ConvertToBoostObj(aDropped))) {}
    private:
        Directorys() = default;

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
class FilesFilter {
    using files_t = std::unordered_map<std::uint64_t, std::vector<boost::filesystem::path>>;
public:
    FilesFilter(const Border::Directorys&& aDirs, const Border::FileBorder&& aFilter) : _Filter(std::move(aFilter)), _Dirs(aDirs) {
        for (const auto& dir : _Dirs.Dirs) {
            FillFiles(dir, 0, _Files);
        }
    }

    files_t& GetFiles() {
        return _Files;
    }
private:
    Border::Directorys _Dirs;
    Border::FileBorder _Filter;
    FilesFilter() = default;
    files_t _Files;

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
                if (!_Filter.IsPermittedSize(obj) || !_Filter.IsPermittedMask(obj)) {
                    continue;
                }
                std::uint64_t size = boost::filesystem::file_size(obj);
                aFiles[size].push_back(obj.path());
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