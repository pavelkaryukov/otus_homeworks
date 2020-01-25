#pragma once

namespace bin_pow
{
    //-----------------------------------------------------------------------------
    constexpr size_t BinExp(int aPow)
    {
        return aPow == 0 ? 1 : 2 * BinExp(--aPow);
    }
    //-----------------------------------------------------------------------------
    constexpr size_t Step(const size_t aNum, const size_t aPow)
    {

        const size_t expValue = BinExp(aPow);
        return (aNum <= expValue) ? aPow : Step(aNum, aPow + 1);
    }
    //-----------------------------------------------------------------------------
    constexpr size_t GetMinBinPow(const size_t aNum)
    {
        if ((aNum == 0) || (aNum == 1))
            return 0;

        return Step(aNum, 0);
    }
    //-----------------------------------------------------------------------------
    void BinPowTest();
    //-----------------------------------------------------------------------------
}

