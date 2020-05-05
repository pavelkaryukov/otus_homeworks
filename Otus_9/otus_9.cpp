#include "cmd_args.h"
#include "file/file_filter.h" 

#include "duplicate/duplicate_finder.h"
//#include <boost/crc.hpp>
//#include <boost/uuid/detail/md5.hpp>
#include "hash/hash_crc32.h"
#include "hash/hash_md5.h"
#include "hash/ihash.h"
#include <boost/filesystem.hpp>     
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>

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
     "c:\\otus_test\\test_directory1",
     "c:\\otus_test\\test_directory2" ,
     "c:\\otus_test\\test_directory1",
     "c:\\otus_test\\test_directory2" 
    };

    std::vector<std::string> dropped = { "c:\\otus_test\\test_directory1\\dont_touch", "c:\\otus_test\\test_directory2\\dont_touch" };
    std::size_t lvl = 1;
    std::size_t minSize = 30'000;
    std::string mask = "*";

    boost::function<std::unique_ptr<IHash>()> factory1 = boost::factory<std::unique_ptr<HashCRC32>>();
    boost::function<std::unique_ptr<IHash>()> factory2 = boost::factory<std::unique_ptr<HashMD5>>();
    auto a1 = factory1();
    auto a2 = factory2();
    a1->ProcessBuffer(dirs[0].data(), dirs[0].size());
    a2->ProcessBuffer(dirs[0].data(), dirs[0].size());
    std::string res1 = a1->Result();
    std::string res2 = a2->Result();

    DuplicateFinder finder1{ boost::factory<std::unique_ptr<HashCRC32>>(), 512};
    auto ressss11 = finder1.TestHash();
    auto ressss12 = finder1.TestHash();

    DuplicateFinder finder2{ boost::factory<std::unique_ptr<HashMD5>>(), 512 };
    auto ressss21 = finder2.TestHash();
    auto ressss22 = finder2.TestHash();

    //Приводи маску к нижнему регистру, приводим имя файла к нижнем регистру
    //перед точкой стави "\" перед звездочкой ставим точку
    FilesFilter fileFilter{ {dirs, dropped, 0}, {minSize, "*"} };
    int stop1 = 0;
    auto files1 = fileFilter.GetFiles();
    auto files2 = fileFilter.GetFiles();
    finder1.GetDuplicated(files1);
    finder2.GetDuplicated(files2);


  
    for (auto&[size, file] : fileFilter.GetFiles()) {
        if (size >= 4'000'000'000) {
            int stop1 = 0;
        }
        int stop1 = 0;
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    TestFileController();
    return 1;
    TestFileSystem();
    try {
        auto args = GetArgs(argc, argv);
        std::cout << "Status:" << std::endl;
        std::cout << args.ToStr() << std::endl;
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