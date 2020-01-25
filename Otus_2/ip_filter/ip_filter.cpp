#include "ip_filter.h"
#include <iostream>
#include <vector>
#include "my_str.h"

//-----------------------------------------------------------------------------
namespace ip_filter
{
    void TestFunc()
    {
        auto test1 = IPv4(0xFF'FE'11'02u);
        auto test1str = test1.ToStr();
        auto test1u = test1.ToUINT32();

        auto test2 = IPv4(0xFFu, 0xFEu, 0x11u, 0x02u);

        auto test2str = test2.ToStr();
        auto test2u = test2.ToUINT32();
        auto test3 = IPv4("172.16.147.35");
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
        IPv4(0u);
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
}