#include "cmd_args.h"
#include "file/file_controller.h"
//#include <boost/crc.hpp>
//#include <boost/uuid/detail/md5.hpp>
#include "hash/hash_crc32.h"
#include "hash/hash_md5.h"
#include "hash/ihash.h"
#include <boost/filesystem.hpp>     
#include <boost/format.hpp>

//"c:\Games\XCOM Chimera Squad\Engine\Stats" 
void TestFileSystem() {
    std::string strPath = "c:\\Games\\XCOM Chimera Squad";
    boost::filesystem::path dirPath{ strPath };
    try {
        if (!boost::filesystem::exists(dirPath)) {
            std::cout << boost::format("������ �������� ������� � ������ [%1%] �� ������") % dirPath << std::endl;
            return;
        }

        if (!boost::filesystem::is_directory(dirPath)) {
            std::cout << boost::format("������ �������� ������� � ������ [%1%] �� �������� ���������") % dirPath << std::endl;
            return;
        }
        auto res = boost::filesystem::directory_entry(dirPath);
        //boost::filesystem::directory_options
        for (auto& x : boost::filesystem::directory_iterator(dirPath)) {
            std::cout << "    " << x.path() << std::endl;
        }

    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void TestFileController() {
    std::vector<std::string> dirs = {
     "c:\\Games\\XCOM Chimera Squad\\_CommonRedist",
     "c:\\Games\\XCOM Chimera Squad\\Binaries" ,
     "c:\\Games\\XCOM Chimera Squad\\Engine",
     "c:\\Games\\XCOM Chimera Squad\\Launcher",
     "c:\\Games\\XCOM Chimera Squad\\XComGame"
    };

    std::vector<std::string> dropped = { "c:\\Games\\XCOM Chimera Squad\\Engine\\Stats" };
    std::size_t lvl = 1;
    std::size_t minSize = 30'000;
    std::string mask = "*";
    FileController controller_3{ {dirs, dropped, 0}, {500, mask} };
    FileController controller_1{ {dirs, dropped, 0}, {1024, mask} };
    FileController controller_0{ {dirs, dropped, 0}, {0, mask} };

    int stop1 = 0;
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    TestFileController();
    return 1;
    TestFileSystem();
    try {
        auto args = GetArgs(argc, argv);
        std::cout << "Status:" << std::endl;
        std::cout << args.Print() << std::endl;
        if (!args.StartProcess)
            return 0;
        //������ ���������
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


//-----------
//using namespace boost::program_options; // ����������
const std::string kBuff = { "Install script for directory: C: / my_programs / otus / otus_homework_process_branch / otus_homeworks / Otus_9" };

std::string TestCrc32_2() {
    std::unique_ptr<IHash> hashPtr = std::make_unique<HashCRC32>();
    hashPtr->ProcessBuffer(kBuff.data(), kBuff.size());
    hashPtr->ProcessBuffer(kBuff.data(), kBuff.size());
    hashPtr->ProcessBuffer(kBuff.data(), kBuff.size());
    return hashPtr->Result();
}

std::string TestCrc32() {
    std::unique_ptr<IHash> hashPtr = std::make_unique<HashCRC32>();
    hashPtr->ProcessBuffer(kBuff.data(), kBuff.size());
    return hashPtr->Result();
}

std::string TestMd5() {
    std::unique_ptr<IHash> hashPtr = std::make_unique<HashMD5>();
    hashPtr->ProcessBuffer(kBuff.data(), kBuff.size());
    return hashPtr->Result();
}

std::string TestMd5_2() {
    std::unique_ptr<IHash> hashPtr = std::make_unique<HashMD5>();
    hashPtr->ProcessBuffer(kBuff.data(), kBuff.size());
    hashPtr->ProcessBuffer(kBuff.data(), kBuff.size());
    hashPtr->ProcessBuffer(kBuff.data(), kBuff.size());
    return hashPtr->Result();
}