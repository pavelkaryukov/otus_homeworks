#pragma once
#include <boost/format.hpp>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

//--dir, D - ���������� ������������ (����� ���� ���������)
//--except, E - ���������� ����������� �� ������������ (����� ���� ���������)
//--lvl, L - ������� ������������ (0 - ������ ������� �������)
//--min, M - ����������� ������ ��������������� ������
//--mask,N - ����� ����� ������, �� �����������������
//--block,S - ������ �����
//--hash, H --�������� ����������� (��������� crc32, md5, ��� ������ ���)
struct CmdArgs {
    enum class HashAlg {
        crc32,
        md5
    };
    //catalog
    std::vector<std::string> Dirs;
    std::vector<std::string> Dropped;
    std::size_t Lvl = 0;
    //file
    std::size_t MinFileSize = 0;
    std::vector<std::string> Masks;
    //hash
    std::size_t BlockSize = 0;
    HashAlg Algorithm = HashAlg::crc32;

    void SetHashAlg(std::string aStr) {
        //�������� �� �������� ���.���  ������ ����� ������������� � ������� ��������
        std::transform(aStr.begin(), aStr.end(), aStr.begin(), [](unsigned char c) { return std::tolower(c); });
        if (aStr == "crc32") {
            Algorithm = HashAlg::crc32;
        }
        else if (aStr == "md5"){
            Algorithm = HashAlg::md5;
        }
        else {
            std::cout << boost::format("����������� has-�������=\"%1%\", ����������� �������� �� ��������� = crc32") % aStr << std::endl;
        }
    }

    std::string Print() {
        std::string res;    
        res += boost::str(boost::format("Dirs:\r\n"));
        for (const auto& dir : Dirs) {
            res += boost::str(boost::format("\t%1%\r\n")%dir);
        }
        res += boost::str(boost::format("Dropped Dirs:\r\n"));
        for (const auto& dir : Dropped) {
            res += boost::str(boost::format("\t%1%\r\n") % dir);
        }
        res += boost::str(boost::format("Lvl: %1%\r\nMinFileSize: %2%\r\n")%Lvl%MinFileSize);
        res += boost::str(boost::format("Masks:\r\n"));
        for (const auto& mask : Masks) {
            res += boost::str(boost::format("\t%1%\r\n") % mask);
        }
        res += boost::str(boost::format("BlockSize: %1%\r\n") % BlockSize);
        std::string strAlg;
        switch (Algorithm) {
            default:
            strAlg += "Unknown";
            break;
            case HashAlg::crc32:
            strAlg += "crc32";
            break;
            case HashAlg::md5:
            strAlg += "md5";
            break;
        }
        return res;
    }
};
