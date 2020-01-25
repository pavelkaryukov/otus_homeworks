#pragma once
#include <cstddef>
namespace bin_pow
{
    //-----------------------------------------------------------------------------
    constexpr std::size_t BinExp(int aPow)
    {
        return aPow == 0 ? 1 : 2 * BinExp(--aPow);
    }
    //-----------------------------------------------------------------------------
    constexpr std::size_t Step(const std::size_t aNum, const std::size_t aPow)
    {

        const std::size_t expValue = BinExp(aPow);
        return (aNum <= expValue) ? aPow : Step(aNum, aPow + 1);
    }
    //-----------------------------------------------------------------------------
    constexpr std::size_t GetMinBinPow(const std::size_t aNum)
    {
        if ((aNum == 0) || (aNum == 1))
            return 0;

        return Step(aNum, 0);
    }
    //-----------------------------------------------------------------------------
    void BinPowTest();
    //-----------------------------------------------------------------------------
}

