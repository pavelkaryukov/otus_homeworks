#pragma once
#include <boost/format.hpp>
#include <cstddef>
#include <string>
#include <type_traits>
#include <vector>
//3*FF = 2FD
//FF + FF + FF = 2FD
class BigNumber {
    using byte_t = std::uint8_t;
public:
    BigNumber() = default;

    template<class TNumber, class = typename std::enable_if_t<std::is_unsigned_v<TNumber>>>
    BigNumber(const TNumber aNumber) {
        *this = aNumber;
    }

    template<class TNumber, class = typename std::enable_if_t<std::is_unsigned_v<TNumber>>>
    BigNumber& operator=(const TNumber aNumber) {
        auto len = sizeof(TNumber);
        auto ptr = (byte_t*)(&aNumber);
        Convert(ptr, len);
        return *this;
    }

    BigNumber& operator+=(const BigNumber& aBn) {
        if (aBn.Size() > Size())
            _Number.resize(aBn.Size());

        byte_t tail = 0;
        for (int i = 0; i < aBn._Number.size(); ++i) {
            std::uint16_t tmp = tail + static_cast<std::uint16_t>(aBn._Number[i]) + static_cast<std::uint16_t>(_Number[i]);
            _Number[i] = tmp & 0xff;
            tail = (tmp & 0xff00) >> 8;
        }
        if (tail > 0)
            _Number.push_back(tail);

        return *this;
    }

    BigNumber operator+(const BigNumber& aRhs) {
        BigNumber res = *this;
        res += aRhs;
        return res;
    }

    BigNumber& operator++() {
        return (*this + 1U);
    }

    BigNumber& operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }


    bool operator==(const BigNumber& aRhs) const {
        auto minLen = std::min(Size(), aRhs.Size());
        bool res = std::equal(_Number.begin(), _Number.begin() + minLen, aRhs._Number.begin(), aRhs._Number.begin() + minLen);
        if (res && (Size() != aRhs.Size())) {
            const auto& withTail = (Size() > aRhs.Size()) ? *this : aRhs;
            res &= withTail.IsZeroTail(minLen);
        }
        return res;
    }

    bool operator!=(const BigNumber& aRhs) const {
        return !(*this == aRhs);
    }

    bool operator>(const BigNumber& aRhs) const {

    }

    bool operator<(const BigNumber& aRhs) const {

    }
    
    bool operator>=(const BigNumber& aRhs) const {
        return *this > aRhs || *this == aRhs;
    }

    bool operator<=(const BigNumber& aRhs) const {
        return *this < aRhs || *this == aRhs;
    }

private:
    std::vector<byte_t> _Number = { {0} };

    void Convert(const byte_t* aPtr, std::size_t aLen) {
        _Number.clear();
        for (auto index = 0; index < aLen; ++index) {
            _Number.push_back(aPtr[index]);
        }
    }

    byte_t& Get(const std::size_t aIndex) {
        if (aIndex >= _Number.size()) {
            int stop1 = 0;
        }
        return _Number[aIndex];
    }

    std::size_t Size() const { 
        return _Number.size();
    }

    bool IsZeroTail(const std::size_t aStartPos) const {
        bool res = true;
        if (aStartPos < _Number.size()) {
            std::for_each(_Number.begin() + aStartPos, _Number.end(), [&res](auto& num) {
                res &= (num == 0);
            });
        }
        return res;
    }
};