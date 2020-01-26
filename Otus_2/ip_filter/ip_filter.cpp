#include "ip_filter.h"
#include "my_str.h"
#include <iostream>
#include <fstream>
//-----------------------------------------------------------------------------
namespace ip_filter
{
    const static std::string kInputDataError = "Input data error";
    void TestFunc()
    {
        auto file = std::ifstream("ip_filter-12995-758870.tsv");
        while (file.is_open()) {
            int stop1;

        }
        auto test1 = IPv4(0xFF'FE'11'02u);
        auto test1str = test1.ToStr();
        auto test1u = test1.ToUINT32();

        auto test2 = IPv4(0xFFu, 0xFEu, 0x11u, 0x02u);

        auto test2str = test2.ToStr();
        auto test2u = test2.ToUINT32();
        auto test3 = IPv4("172.16.147.35");
        auto test4 = IPv4("192.168.0.35");      
        auto test5 = IPv4("256.16.147.35");
        auto test3str = test3.ToStr();
        auto test3u = test3.ToUINT32();
        int stop1 = 0;
    }
    //-----------------------------------------------------------------------------
    IPv4::IPv4(std::uint8_t aIP_1, std::uint8_t aIP_2, std::uint8_t aIP_3, std::uint8_t aIP_4)
    {
        m_IP = std::tie(aIP_1, aIP_2, aIP_3, aIP_4);
    }                                                                              
    //-----------------------------------------------------------------------------
    IPv4::IPv4(std::uint32_t aIPv4)//
    {
        const auto ptr = (std::uint8_t*)&aIPv4;
        m_IP = std::tie(ptr[3], ptr[2], ptr[1], ptr[0]);
    }                                                                              
    //-----------------------------------------------------------------------------
    IPv4::IPv4(std::string aIPv4)
    {
        auto str = aIPv4;
        static const std::string kDelimeters = ".\x20";
        auto numbers = mystr::GetAllNumbers(aIPv4, kDelimeters);
        if (numbers.size() > std::tuple_size<decltype(m_IP)>::value) {
            std::cout << "Input data error: to many bytes for IPv4"<<std::endl;
        }
        auto lambda1 = [](std::size_t aDigit) {
            return aDigit<=0xff;
        };
        auto res = mystr::ConvertStrArrayToNumbers(numbers, lambda1);
        if (res.empty()) {
            std::cout << "Input data error: one or few numbers more 255 (byte range)" << std::endl;
            return;
        }

        m_IP = ConvertVectToIPv4(res);
    }
    //-----------------------------------------------------------------------------
    std::string IPv4::ToStr()
    {
        const auto&[a1, a2, a3, a4] = m_IP;
        return mystr::Fmt("%u.%u.%u.%u", a1, a2, a3, a4);
    }
    //-----------------------------------------------------------------------------
    std::uint32_t IPv4::ToUINT32()
    {
        return *(std::uint32_t*)&m_IP;
    }
    //-----------------------------------------------------------------------------
    bool IPv4::IsCorrectNumber(std::size_t aDigit)
    {
        return aDigit <= 0xff;
    }
    //-----------------------------------------------------------------------------
    ip_filter::IPv4::IPv4Data IPv4::ConvertVectToIPv4(std::vector<std::size_t>& aVect)
    {
        static const std::size_t  kSizeOfTuple = std::tuple_size<decltype(m_IP)>::value;
        if (aVect.size() > kSizeOfTuple) 
            return {};

        if (aVect.size() < kSizeOfTuple) {
            for (auto i = aVect.size(); i < kSizeOfTuple; ++i) {
                aVect.emplace_back(0);
            }
        }
        return std::tie(aVect[0], aVect[1], aVect[2], aVect[3]);//Так как вектор берется из строки то предполагаем что первый элемент - больший
    }
    //-----------------------------------------------------------------------------
}