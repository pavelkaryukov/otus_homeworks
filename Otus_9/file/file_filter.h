#pragma once
#include "file/dir_border.h" 
#include "file/file_border.h"
#include "file/file_hash.h"
#include <boost/format.hpp>
#include <unordered_map> 
/**
* \brief  Класс обеспечивает удобный для наших задач доступ к файловой системе, отбор файлов с учетом маски, размера, глубины вложения каталогов.
*/
class FilesFilter {
    using files_t = std::unordered_map<std::uint64_t, std::set<boost::filesystem::path>>;
public:
    FilesFilter(const DirBorder&& aDirs, const FileBorder&& aFilter) : _filter(std::move(aFilter)), _dirs(aDirs) {
        for (const auto& dir : _dirs.Dirs) {
            FillFiles(dir, 0, _files);
        }
    }

    /**
    * \brief  Получить файлы, среди которых можно искать дубликаты
    * \details будут отсеяны файлы из запрещенных каталого, не соответвующие маски имени или размера
    * \return  мапа где ключ - размер файлов, а значение список имен файлов (boost::filesystem::path)
    */
    files_t& GetFiles() {
        return _files;
    }
private:
    DirBorder _dirs;
    FileBorder _filter;
    FilesFilter() = default;
    files_t _files;

    void FillFiles(const boost::filesystem::path& aDir, const std::size_t aLvl, files_t& aFiles) {
        if (aLvl > _dirs.Lvl)
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
                if (!_filter.IsPermittedFile(obj)) {
                    continue;
                }
                std::uint64_t size = boost::filesystem::file_size(obj);
                aFiles[size].insert({ obj.path() });
            }
        }
    }
};