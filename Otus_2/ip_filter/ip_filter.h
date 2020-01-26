#pragma once
#include <tuple>
#include <cstdint>
#include <string>
#include <vector>
#include <functional>
namespace ip_filter
{    
    
    struct IPv4
    {
        using IPv4Data = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>;
        //constructors
        IPv4() = default;
        IPv4(std::uint8_t aIP_1, std::uint8_t aIP_2, std::uint8_t aIP_3, std::uint8_t aIP_4 );
        explicit IPv4(std::uint32_t aIPv4);//старший байт слева в IP
        explicit IPv4(std::string aIPv4);
        //To
        std::string ToStr() const;
        std::uint32_t ToUINT32() const;
        bool Empty() const;

        bool operator < (const IPv4& rhs) const
        {
            return ToUINT32() < rhs.ToUINT32();
        }

        bool operator > (const IPv4& rhs) const
        {
            return ToUINT32() > rhs.ToUINT32();
        }
        //
        std::uint8_t GetByte1() const;
        std::uint8_t GetByte2() const;
        std::uint8_t GetByte3() const;
        std::uint8_t GetByte4() const;
    private: 
        IPv4Data m_IP;
        static bool IsCorrectNumber(std::size_t aDigit);
        IPv4Data ConvertVectToIPv4(std::vector<std::size_t>& aVect);

        //friend std::vector<IPv4> Filter(const std::vector<IPv4>& aIpVect, const std::uint8_t aFirstByte); //Переделать на std::function
        //friend std::vector<IPv4> Filter(const std::vector<IPv4>& aIpVect, std::function<bool(IPv4)> aCondition, const bool aFilterAll);
    };
    //-----------------------------------------------------------------------------
    //std::vector<IPv4> Filter(const std::vector<IPv4>& aIpVect, const std::uint8_t aFirstByte);
    //-----------------------------------------------------------------------------
    std::vector<IPv4> Filter(const std::vector<IPv4>& aIpVect, std::function<bool(IPv4)> aCondition, const bool aFilterAll = false);
    //-----------------------------------------------------------------------------
    void FillIpVect(std::string aStr, std::vector<IPv4>& aIpVect);
    //-----------------------------------------------------------------------------
    std::string IpListToStr(const std::vector<IPv4>& aIpVect);
    //-----------------------------------------------------------------------------
    void TestFunc();
    //-----------------------------------------------------------------------------
}
