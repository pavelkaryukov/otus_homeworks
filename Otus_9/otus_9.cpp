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
            std::cout << boost::format("Объект файловой системы с именем [%1%] не найден") % dirPath << std::endl;
            return;
        }

        if (!boost::filesystem::is_directory(dirPath)) {
            std::cout << boost::format("Объект файловой системы с именем [%1%] не является каталогом") % dirPath << std::endl;
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

    //Приводи маску к нижнему регистру, приводим имя файла к нижнем регистру
    //перед точкой стави "\" перед звездочкой ставим точку
    FileController controller_1{ {dirs, {}, 0}, {0, "Base*.bin"} };
    FileController controller_2{ {dirs, {}, 0}, {0, "base*.bin"} };
    FileController controller_3{ {dirs, dropped, 0}, {0, "*.ini"} }; //перед точкой ".*\.ini"
    FileController controller_0{ {dirs, dropped, 0}, {0, "*.dll"} };
    FileController controller_4{ {dirs, dropped, 0}, {0, "*ase*"} };

    //FileController controller_3{ {dirs, dropped, 0}, {0, "somefiles.*\.txt"} };
    //FileController controller_1{ {dirs, dropped, 0}, {0, "somefiles.*\.cab"} };
    //FileController controller_0{ {dirs, dropped, 0}, {0, "somefiles.*\.ini"} };

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
        //Начать обработку
    } 
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}

//--dir, D - директория сканирования (может быть несколько)
//--except, E - директория исключенная из сканирования (может быть несколько)
//--lvl, L - уровень сканирования (0 - только текущий каталог)
//--min, M - минимальный размер рассматриваемых файлов
//--mask,N - маски имени файлов, не регистрозависимые
//--block,S - размер блока
//--hash, H --алгоритм хэширования (реализуем crc32, md5, что нибудь ещё)

//1.обработка командной строки -> boost
//2.нахождение файлов, необходимых для анализа (соответсвует маске, размеру и тд...)
//3.хеширование файлов и их сравнение.
//4.вывод дубликатов 


//-----------
//using namespace boost::program_options; // переделать
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