#include "cmd_args.h"
#include <boost/program_options.hpp>
#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>

using namespace boost::program_options; // ����������
const std::string kBuff = {"Install script for directory: C: / my_programs / otus / otus_homework_process_branch / otus_homeworks / Otus_9"};

std::size_t TestCrc32_2() {
    boost::crc_32_type  result;
    result.process_bytes(kBuff.data(), kBuff.size());
    result.process_bytes(kBuff.data(), kBuff.size());
    result.process_bytes(kBuff.data(), kBuff.size());
    auto hash = result.checksum();
    return hash;
}

std::size_t TestCrc32() {
    boost::crc_32_type  result;
    result.process_bytes(kBuff.data(), kBuff.size());
    auto hash = result.checksum();
    return hash;
}

std::string TestMd5() {
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;

    hash.process_bytes(kBuff.data(), kBuff.size());
    hash.get_digest(digest);

    std::string res;
    for (auto& elem : digest) {
        res += boost::str(boost::format("[%1%]") % elem);
    }
    return res;
}

std::string TestMd5_2() {
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;

    hash.process_bytes(kBuff.data(), kBuff.size());
    hash.process_bytes(kBuff.data(), kBuff.size());
    hash.process_bytes(kBuff.data(), kBuff.size());
    hash.get_digest(digest);

    std::string res;
    for (auto& elem : digest) {
        res += boost::str(boost::format("[%1%]") % elem);
    }
    return res;
}


CmdArgs GetArgs(int argc, char** argv) {
    CmdArgs procArgs;
    std::string hash;
    options_description desc{ "Options" };//TODO::������� ����������� ������ �� ���������� ��������� ������� ?
    desc.add_options()
        ("help,h", "Help screen")
        ("dir,D", value<std::vector<std::string>>(&procArgs.Dirs), "���������� ������������ (����� ���� ���������)")
        ("except,E", value<std::vector<std::string>>(&procArgs.Dropped), "���������� ����������� �� ������������ (����� ���� ���������)")
        ("lvl,L", value<std::size_t>(&procArgs.Lvl), "������� ������������ (0 - ������ ������� �������)")
        ("min,M", value<std::size_t>(&procArgs.MinFileSize), "����������� ������ ��������������� ������ (0 - ��� �����������)")
        ("mask,N", value<std::vector<std::string>>(&procArgs.Masks), "����� ����� ������, �� ����������������� (����� ���� ���������)")
        ("hash,H", value<std::string>(&hash), "�������� ����������� (��������� crc32, md5, ��� ������ ���)");

    command_line_parser parser{ argc, argv };
    parser.options(desc).allow_unregistered().style(
        command_line_style::default_style |
        command_line_style::allow_slash_for_short);
    parsed_options parsed_options = parser.run();

    variables_map vm;
    store(parsed_options, vm);
    notify(vm);

    if (vm.count("help"))
        std::cout << desc << '\n';
    else {
        procArgs.SetHashAlg(hash);
        std::cout << "Lets get the party start" << std::endl;
    }
    return procArgs;
}


int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    auto str1 = TestMd5();
    auto str2 = TestMd5_2();
    auto crc32_1 = TestCrc32();//0xf75f07ad
    auto crc32_2 = TestCrc32_2();//0xf75f07ad
    try {
        auto args = GetArgs(argc, argv);
        std::cout << "Status:" << std::endl;
        std::cout << args.Print() << std::endl;
    } 
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}

//--dir, D - ���������� ������������ (����� ���� ���������)
//--except, E - ���������� ����������� �� ������������ (����� ���� ���������)
//--lvl, L - ������� ������������ (0 - ������ ������� �������)
//--min, M - ����������� ������ ��������������� ������
//--mask,N - ����� ����� ������, �� �����������������
//--block,S - ������ �����
//--hash, H --�������� ����������� (��������� crc32, md5, ��� ������ ���)

//1.��������� ��������� ������ -> boost
//2.���������� ������, ����������� ��� ������� (������������ �����, ������� � ��...)
//3.����������� ������ � �� ���������.
//4.����� ���������� 
