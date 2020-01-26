#pragma once
#include <tuple>
#include <cstdint>
#include <string>
#include <vector>

namespace ip_filter
{
    void TestFunc();
    struct IPv4
    {
        using IPv4Data = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>;
        //constructors
        IPv4() = default;
        IPv4(std::uint8_t aIP_1, std::uint8_t aIP_2, std::uint8_t aIP_3, std::uint8_t aIP_4 );
        explicit IPv4(std::uint32_t aIPv4);//старший байт слева в IP
        explicit IPv4(std::string aIPv4);
        //To
        std::string ToStr();
        std::uint32_t ToUINT32();
    private: 
        IPv4Data m_IP;
        static bool IsCorrectNumber(std::size_t aDigit);
        IPv4Data ConvertVectToIPv4(std::vector<std::size_t>& aVect);
    };
}
