#pragma once
#include <boost/filesystem.hpp>     
#include <string>
#include <set>
#include <vector>
///\brief ��������� ������ � ���� ���� � ���������, ���� � ���������, ������� ��������� � ������ ����������, ������� ���������
struct DirBorder {
    
    ///\brief ��������, ��� �������������� ����� ����������
    const std::set<boost::filesystem::path> Dirs;
    ///\brief �������� ��� �� ����� ������������ ����� ����������
    const std::set<boost::filesystem::path> Dropped;
    ///\brief ������� ������ - 0 ������ ������� �������
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
