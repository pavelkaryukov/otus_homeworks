#include "duplicate/duplicate_finder.h"
#include "file/file_filter.h" 
#include "hash/hash_crc32.h"
#include "hash/ihash.h"
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h> 

TEST(test_bayan, test_bayan_1) {
    const std::string expectedOutput = "\"file_1.lib\"\"file_1.txt\"\"file_2.lib\"\"file_2.txt\"\"file_3.lib\"\"file_3.txt\"";
    testing::internal::CaptureStdout();
    //файлы file_4.lib file_4.txt  ¤вл¤ютс¤ уникальными
    FilesFilter fileFilter{ {{ "test_catalog" } , {}, 0}, {0, {"*"}} };
    DuplicateFinder finder{ boost::factory<std::unique_ptr<HashCRC32>>(), 50 };
    finder.OutputDuplicated(fileFilter.GetFiles(), false);
    std::string outputStr = testing::internal::GetCapturedStdout();
    boost::erase_all(outputStr, "\r");
    boost::erase_all(outputStr, "\n");
    ASSERT_STRCASEEQ(expectedOutput.c_str(), outputStr.c_str());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}