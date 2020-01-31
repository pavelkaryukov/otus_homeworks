#include "ip_filter.h"
#include "my_str.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
//#include <filesystem>
//#include <boost/uuid/detail/md5.hpp>
//-----------------------------------------------------------------------------
namespace ip_filter
{
    const static std::string kInputDataError = "Input data error";
    //-----------------------------------------------------------------------------
//     std::vector<ip_filter::IPv4> Filter(const std::vector<IPv4>& aIpVect, const std::uint8_t aFirstByte)
//     {
//         auto filtered = std::vector<ip_filter::IPv4>();
//         for (const auto& ip : aIpVect) {
//             if (ip.GetByte1() == aFirstByte) {
//                 filtered.emplace_back(ip);
//             }
//         }
//         return filtered;
//     }
    //-----------------------------------------------------------------------------
    std::vector<ip_filter::IPv4> Filter(const std::vector<IPv4>& aIpVect, std::function<bool(IPv4)> aCondition, const bool aFilterAll /*= false*/)
    {
        auto filtered = std::vector<ip_filter::IPv4>();
        bool elementWasFinded = false;
        for (const auto& ip : aIpVect) {
            if (aCondition(ip)) {
                filtered.emplace_back(ip);
                elementWasFinded = true;
            } else  if (!aFilterAll && elementWasFinded){
                break; 
            }
        }
        return filtered;
    }
//-----------------------------------------------------------------------------
    void FillIpVect(std::string aStr, std::vector<IPv4>& aIpVect)
    {
        auto strIp = mystr::GetTokens(aStr, "\t\x20");
        if (strIp.empty())
            return;
        auto ipv4 = IPv4(strIp[0]);
        if (ipv4.Empty())
            return;

        aIpVect.emplace_back(ipv4);
    }
    //-----------------------------------------------------------------------------
    bool CmpLess(const IPv4 &a, const IPv4 &b)
    {
        return a < b;
    }
    //-----------------------------------------------------------------------------
    bool CmpMore(const IPv4 &a, const IPv4 &b)
    {
        return a > b;
    }
    //-----------------------------------------------------------------------------
    std::string IpListToStr(const std::vector<IPv4>& aIpVect)
    {
        std::string str;
        for (const auto& ip : aIpVect) {
            str += mystr::Fmt("%s\n", ip.ToStr().c_str());
        }
        return str;
    }
    //-----------------------------------------------------------------------------
    void TestFunc()
    {
        //auto infile = std::ifstream("ip_filter-12995-758870.tsv");
        //c:\my_programs\otus\otus_homeworks\Otus_2\examples\ip_filter-12995-758870.tsv 
        //auto infile = std::ifstream("c:\\my_programs\\otus\\otus_homeworks\\Otus_2\\examples\\ip_filter-12995-758870.tsv");
        //auto test1 = std::filesystem::current_path();
        //auto testFilePath = std::filesystem::current_path()/".."/"Otus_2"/"ip_filter-12995-758870.tsv";
        auto testFilePath = "ip_filter-12995-758870.tsv";

        auto infile = std::ifstream(testFilePath);
        if (!infile.is_open())
            return;
        std::cout << "file is opened" << std::endl;
        std::string str;
        std::vector<IPv4> ipVect;
        while (std::getline(infile, str)) {
            FillIpVect(str, ipVect);
        }
        

        std::sort(ipVect.begin(), ipVect.end(), CmpLess); // лексеграфический порядок
        auto str1 = IpListToStr(ipVect);
        std::sort(ipVect.begin(), ipVect.end(), CmpMore);// обратный лексеграфический порядок
        auto sortedStr = IpListToStr(ipVect);

        auto a1 = [](IPv4 aIP)->bool {
            return aIP.GetByte1() == 1;
        };

        auto a2 = [](IPv4 aIP)->bool {
            return (aIP.GetByte1() == 46) && (aIP.GetByte2() == 70);
        };

        auto a_any = [](IPv4 aIP)->bool {
            return (aIP.GetByte1() == 46) || (aIP.GetByte2() == 46) || (aIP.GetByte3() == 46) || (aIP.GetByte4() == 46);
        };



        auto filtered1 = Filter(ipVect, a1);
        auto filtered1Str = IpListToStr(filtered1);

        
        auto filtered2 = Filter(ipVect, a2);
        auto filtered2Str = IpListToStr(filtered2);


        auto filteredAny = Filter(ipVect, a_any, true);
        auto filteredAnyStr = IpListToStr(filteredAny);
        std::string resStr = sortedStr + filtered1Str + filtered2Str +filteredAnyStr;
        std::ofstream resfile("filtered_ip.txt");
        resfile << resStr;
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
        auto numbers = mystr::GetTokens(aIPv4, kDelimeters, mystr::IsCorrectNumber);
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
    std::string IPv4::ToStr() const
    {
        const auto&[a1, a2, a3, a4] = m_IP;
        return mystr::Fmt("%u.%u.%u.%u", a1, a2, a3, a4);
    }
    //-----------------------------------------------------------------------------
    std::uint32_t IPv4::ToUINT32() const
    {
        return *(std::uint32_t*)&m_IP;
    }
    //-----------------------------------------------------------------------------
    bool IPv4::Empty() const
    {
        return ToUINT32() == 0;
    }
    //-----------------------------------------------------------------------------
    std::uint8_t IPv4::GetByte1() const
    {
        return std::get<0>(m_IP);
    }
    //-----------------------------------------------------------------------------
    std::uint8_t IPv4::GetByte2() const
    {
        return std::get<1>(m_IP);
    }
    //-----------------------------------------------------------------------------
    std::uint8_t IPv4::GetByte3() const
    {
        return std::get<2>(m_IP);
    }
    //-----------------------------------------------------------------------------
    std::uint8_t IPv4::GetByte4() const
    {
        return std::get<3>(m_IP);
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