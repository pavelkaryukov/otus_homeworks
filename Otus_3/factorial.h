#pragma once

constexpr std::size_t Factorial(const std::size_t aNum)
{
    return  (aNum > 0) ? aNum * Factorial(aNum - 1) : 1;
}
