#pragma once
#include "file/file_hash.h"
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>     
#include <boost/format.hpp> 
#include <boost/regex.hpp>
#include <set>
#include <unordered_map> 
#include <vector>

namespace Borders {
    class FileBorder {
    public:
        FileBorder(const std::size_t aMinSize, const std::vector<std::string>&  aMasks) : 
            _minSize(aMinSize != 0 ? aMinSize : 1), _filter(MaskToRegexVect(aMasks)) {
        }

        bool IsPermittedSize(const boost::filesystem::directory_entry& aObj) const {
            return  (_minSize == 0) || (boost::filesystem::file_size(aObj) >= _minSize);
        }

        bool IsPermittedMask(const boost::filesystem::directory_entry& aObj) const {            
            std::string filename = aObj.path().filename().string();
            std::transform(filename.begin(), filename.end(), filename.begin(), [](unsigned char c) { return std::tolower(c); });
            bool res = false;
            for (auto& filter : _filter) {
                if (filter.str() == "*" || filter.str() == "")
                    return true;
                boost::smatch what;
                res |= boost::regex_match(filename, what, filter);
            }
            return res;
        }
    private:
        FileBorder() = default;
        const std::size_t  _minSize = 0;
        const std::vector<boost::regex> _filter { boost::regex("") };
       
        std::vector<boost::regex> MaskToRegexVect(const std::vector<std::string>& aMasks) {
            std::vector<boost::regex> res;
            for (auto& mask : aMasks) {
                res.emplace_back(boost::regex( MaskToRegex(mask)));
            }
            if (res.empty()) {
                res.emplace_back(boost::regex(""));
            }
            return res;
        }

        std::string MaskToRegex(std::string aStr) {
            std::transform(aStr.begin(), aStr.end(), aStr.begin(), [](unsigned char c) { return std::tolower(c); });            
            boost::replace_all(aStr, ".", "\.");
            boost::replace_all(aStr, "*", ".*");
            return aStr;
        }
    };

    struct Directories {
        const std::set<boost::filesystem::path> Dirs;
        const std::set<boost::filesystem::path> Dropped;
        const std::size_t Lvl = 0;
        Directories(const std::vector<std::string>& aDirs, const std::vector<std::string>& aDropped, const std::size_t aLvl)
            : Lvl(aLvl), Dirs(std::move(ConvertToBoostObj(aDirs))), Dropped(std::move(ConvertToBoostObj(aDropped))) {}
    private:
        Directories() = default;

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
    using files_t = std::unordered_map<std::uint64_t, std::set<boost::filesystem::path>>;
public:
    FilesFilter(const Borders::Directories&& aDirs, const Borders::FileBorder&& aFilter) : _filter(std::move(aFilter)), _dirs(aDirs) {
        for (const auto& dir : _dirs.Dirs) {
            FillFiles(dir, 0, _files);
        }
    }

    files_t& GetFiles() {
        return _files;
    }
private:
    Borders::Directories _dirs;
    Borders::FileBorder _filter;
    FilesFilter() = default;
    files_t _files;

    void FillFiles(const boost::filesystem::path& aDir, const std::size_t aLvl, files_t& aFiles) {
        if (_dirs.Lvl != 0 && aLvl >= _dirs.Lvl)
            return;

        if (_dirs.Dropped.find(aDir) != _dirs.Dropped.end())
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
                if (!_filter.IsPermittedSize(obj) || !_filter.IsPermittedMask(obj)) {
                    continue;
                }
                std::uint64_t size = boost::filesystem::file_size(obj);
                aFiles[size].insert({ obj.path() });
            }
        }
    }
};