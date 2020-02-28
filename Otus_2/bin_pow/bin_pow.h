#pragma once
#include <cstddef>
namespace bin_pow
{
    //-----------------------------------------------------------------------------
    constexpr std::size_t BinExp(int aPow)
    {
        return static_cast<std::size_t>(1) << aPow;
    }
    //-----------------------------------------------------------------------------
    static constexpr size_t  kBinPowArray[32] =
    {
         BinExp(0),
         BinExp(1),
         BinExp(2),
         BinExp(3),
         BinExp(4),
         BinExp(5),
         BinExp(6),
         BinExp(7),
         BinExp(8),
         BinExp(9),
         BinExp(10),
         BinExp(11),
         BinExp(12),
         BinExp(13),
         BinExp(14),
         BinExp(15),
         BinExp(16),
         BinExp(17),
         BinExp(18),
         BinExp(19),
         BinExp(20),
         BinExp(21),
         BinExp(22),
         BinExp(23),
         BinExp(24),
         BinExp(25),
         BinExp(26),
         BinExp(27),
         BinExp(28),
         BinExp(29),
         BinExp(30),
         BinExp(31)
    };
    //-----------------------------------------------------------------------------
    constexpr std::size_t Step(const std::size_t aNum, const std::size_t aPow)
    {
        if (aPow > sizeof(kBinPowArray))
            return sizeof(kBinPowArray) + 1;

        return (aNum <= kBinPowArray[aPow]) ? aPow : Step(aNum, aPow + 1);
    }
    //-----------------------------------------------------------------------------
    constexpr std::size_t GetMinBinPow(const std::size_t aNum)
    {
        return Step(aNum, 0);
    }
    //-----------------------------------------------------------------------------
    void BinPowTest();
    //-----------------------------------------------------------------------------
}

