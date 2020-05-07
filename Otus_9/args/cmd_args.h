#pragma once
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
//using namespace boost::program_options::;
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
    bool StartProcess = false;
    
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
            std::cout << boost::format("����������� hash-�������=\"%1%\", ����������� �������� �� ��������� = crc32") % aStr << std::endl;
        }
    }

    std::string ToStr() {
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

CmdArgs GetArgs(int argc, char** argv) {
    CmdArgs procArgs;
    std::string hash;
    boost::program_options::options_description desc{ "Options" };//TODO::������� ����������� ������ �� ���������� ��������� ������� ?
    desc.add_options()
        ("help,h", "Help screen")
        ("dir,D", boost::program_options::value<std::vector<std::string>>(&procArgs.Dirs), "���������� ������������ (����� ���� ���������)")
        ("except,E", boost::program_options::value<std::vector<std::string>>(&procArgs.Dropped), "���������� ����������� �� ������������ (����� ���� ���������)")
        ("lvl,L", boost::program_options::value<std::size_t>(&procArgs.Lvl), "������� ������������ (0 - ������ ������� �������)")
        ("min,M", boost::program_options::value<std::size_t>(&procArgs.MinFileSize), "����������� ������ ��������������� ������ (0 - ��� �����������)")
        ("mask,N", boost::program_options::value<std::vector<std::string>>(&procArgs.Masks), "����� ����� ������, �� ����������������� (����� ���� ���������)")
        ("block,B", boost::program_options::value<std::size_t>(&procArgs.BlockSize), "������ ������������� �����")
        ("hash,H", boost::program_options::value<std::string>(&hash), "�������� ����������� (��������� crc32, md5, ��� ������ ���)");

    boost::program_options::command_line_parser parser{ argc, argv };
    parser.options(desc).allow_unregistered().style(
        boost::program_options::command_line_style::default_style |
        boost::program_options::command_line_style::allow_slash_for_short
    );
    boost::program_options::parsed_options parsed_options = parser.run();

    boost::program_options::variables_map vm;
    boost::program_options::store(parsed_options, vm);
    boost::program_options::notify(vm);
    if (procArgs.Dirs.empty()) {
        std::cout << "�.�. �������� --dir �� ��� ����������,  ����� ���������� ����� ����������� � ������� ��������" << std::endl;
        procArgs.Dirs = { "." };
    }

    if (vm.count("help"))
        std::cout << desc << '\n';
    else {
        procArgs.SetHashAlg(hash);
        procArgs.StartProcess = true;
    }
    return procArgs;
}