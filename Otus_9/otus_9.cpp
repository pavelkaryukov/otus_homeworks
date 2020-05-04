#include "cmd_args.h"
//#include <boost/crc.hpp>
//#include <boost/uuid/detail/md5.hpp>
#include "hash/hash_crc32.h"
#include "hash/hash_md5.h"
#include "hash/ihash.h"

//using namespace boost::program_options; // ����������
const std::string kBuff = {"Install script for directory: C: / my_programs / otus / otus_homework_process_branch / otus_homeworks / Otus_9"};

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

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    auto str1 = TestMd5();
    auto str2 = TestMd5_2();
    auto crc32_1 = TestCrc32();//0xf75f07ad
    auto crc32_2 = TestCrc32_2();
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
