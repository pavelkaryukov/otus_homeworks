#pragma once
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>     
#include <boost/regex.hpp>
#include <string>
#include <vector>
///\brief класс фильтрующий файлы по размеру и маске
class FileBorder {
public:
    FileBorder(const std::size_t aMinSize, const std::vector<std::string>&  aMasks) :
        _minSize(aMinSize != 0 ? aMinSize : 1), _filter(MaskToRegexVect(aMasks)) {}
    
    /**
    * \brief  файл разрешен для поиска дубликатов
    * \details проверяет файл на соотвесткие маски имени и размера
    */
    bool IsPermittedFile(const boost::filesystem::directory_entry& aObj) {
        return IsPermittedSize(aObj) && IsPermittedMask(aObj);
    }

private:
    FileBorder() = default;
    const std::size_t  _minSize = 0;
    const std::vector<boost::regex> _filter{ boost::regex("") };

    std::vector<boost::regex> MaskToRegexVect(const std::vector<std::string>& aMasks) {
        std::vector<boost::regex> res;
        for (auto& mask : aMasks) {
            res.emplace_back(boost::regex(MaskToRegex(mask)));
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
};