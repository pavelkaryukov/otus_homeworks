#pragma once
#include <boost/format.hpp>
#include <iomanip>
#include <cstddef>
#include <iostream> 
#include <string>
#include <type_traits>
#include <vector>
class BigNumber {
    using byte_t = std::uint8_t;
public:
    BigNumber() = default;
    
    BigNumber(const std::vector<byte_t>& aVect) {
        _Data.clear();
        _Data.insert(_Data.begin(), aVect.crbegin(), aVect.crend());
    }

    template<class TNumber, class = typename std::enable_if_t<std::is_integral_v<TNumber>>>
    BigNumber(const TNumber aNumber) {
        if (aNumber < 0)
            throw std::logic_error("class BigNumber: constructor BigNumber<TNumber >(const TNumber aNumber): aNumber < 0");
        *this = aNumber;
    }

    template<class TNumber, class = typename std::enable_if_t<std::is_integral_v<TNumber>>>
    BigNumber& operator=(const TNumber aNumber) {
        if (aNumber < 0)
            throw std::logic_error("class BigNumber: operator BigNumber& operator=(const TNumber aNumber): aNumber < 0");
        _Data.clear();
        AddNumber(aNumber);
        return *this;
    }

    void Decrement(const std::size_t aPos) {
        if (aPos >= RealSize())
            throw std::logic_error("BigNumber: method Decrement: negative number");
        if (_Data[aPos] == 0) {
            _Data[aPos] = std::numeric_limits<byte_t>::max();
            Decrement(aPos + 1);
            return;
        }
        _Data[aPos] -= 1;
    }

    template<class TNumber, class = typename std::enable_if_t<std::is_integral_v<TNumber>>>
    operator TNumber() {
        const auto len = std::min(sizeof(TNumber), RealSize());
        TNumber res = 0;
        for (int i = 0; i < len; ++i) {
            res |= static_cast<TNumber>(_Data[i]) << (8 * i);
        }
        return res;
    }

    template<class TNumber, class = typename std::enable_if_t<std::is_integral_v<TNumber>>>
    BigNumber& operator*=(const TNumber aNumber) {
        if (aNumber < 0)
            throw std::logic_error("BigNumber: operator*=: negative number");
        const auto tmp = *this;
        for (int i = 1; i < aNumber; ++i) {
            *this += tmp;
        }
        return *this;
    }

    template<class TNumber, class = typename std::enable_if_t<std::is_integral_v<TNumber>>>
    friend BigNumber operator*(const BigNumber& aBn, const TNumber aNumber) {
        BigNumber bn = aBn;
        bn *= aNumber;
        return bn;
    }

    template<class TNumber, class = typename std::enable_if_t<std::is_integral_v<TNumber>>>
    friend BigNumber operator*(const TNumber aNumber, const BigNumber& aBn) {
        BigNumber bn = aBn;
        bn *= aNumber;
        return bn;
    }

    BigNumber& operator-=(const BigNumber& aRhs) {
        if (*this < aRhs)
            throw std::logic_error("BigNumber: operator-=: negative number");

        std::size_t len = std::min(RealSize(), aRhs.RealSize());
        for (auto i = 0U; i < len; ++i) {
            if (_Data[i] < aRhs._Data[i]) {
                auto tmp = aRhs._Data[i] - _Data[i];
                _Data[i] = 0;
                Decrement(i);
                _Data[i] -= tmp;
                ++_Data[i];
                continue;
            }
            _Data[i] -= aRhs._Data[i];
        }
        return *this;
    }

    BigNumber operator-(const BigNumber& aRhs) {
        BigNumber res = *this;
        res -= aRhs;
        return res;
    }

    BigNumber& operator+=(const BigNumber& aRhs) {
        if (aRhs.RealSize() > RealSize())
            _Data.resize(aRhs.RealSize());

        byte_t tail = 0;
        for (auto i = 0U; i < aRhs.RealSize(); ++i) {
            std::uint16_t tmp = tail + static_cast<std::uint16_t>(aRhs._Data[i]) + static_cast<std::uint16_t>(_Data[i]);
            _Data[i] = tmp & 0xff;
            tail = (tmp & 0xff00) >> 8;
        }
        if (tail > 0) {
            AddElementInPos(aRhs.RealSize(), tail);
        }
        return *this;
    }

    BigNumber operator+(const BigNumber& aRhs) {
        BigNumber res = *this;
        res += aRhs;
        return res;
    }

    BigNumber& operator++() {
        *this += 1;
        return *this;
    }

    BigNumber& operator++(int) {
        BigNumber tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const BigNumber& aRhs) const {
        auto minLen = std::min(RealSize(), aRhs.RealSize());
        bool res = std::equal(_Data.begin(), _Data.begin() + minLen, aRhs._Data.begin(), aRhs._Data.begin() + minLen);
        if (res && (RealSize() != aRhs.RealSize())) {
            return false;
        }
        return res;
    }

    bool operator!=(const BigNumber& aRhs) const {
        return !(*this == aRhs);
    }

    bool operator>(const BigNumber& aRhs) const {
        if (RealSize() < aRhs.RealSize()) {
            return false;
        } 
        else if (RealSize() > aRhs.RealSize()) {
            return true;
        }

        if (aRhs.RealSize() == 0)
            return false;//  в таком случае они равны

        for (int index = aRhs.RealSize() - 1; index >= 0; --index) {
            if (_Data[index] > aRhs._Data[index])
                return true;
            else if (_Data[index] < aRhs._Data[index])
                return false;
        }
        return false;
    }

    bool operator<(const BigNumber& aRhs) const {
        return !(*this > aRhs) && (*this != aRhs);
    }
    
    bool operator>=(const BigNumber& aRhs) const {
        return *this > aRhs || *this == aRhs;
    }

    bool operator<=(const BigNumber& aRhs) const {
        return *this < aRhs || *this == aRhs;
    }
private:
    std::vector<byte_t> _Data = { {0} };

    template<class TNumber, class = typename std::enable_if_t<std::is_integral_v<TNumber>>>
    void AddNumber(const TNumber aNumber) {
        auto len = sizeof(TNumber);
        auto ptr = (byte_t*)(&aNumber);
        AddArray(ptr, len);
    }

    void AddArray(const byte_t* aPtr, std::size_t aLen) {
        for (auto index = 0U; index < aLen; ++index) {
            _Data.push_back(aPtr[index]);
        }
    }

    std::size_t RealSize() const {
        auto iter = _Data.crbegin();
        for (; iter != _Data.crend(); ++iter) {
            if (*iter != 0)
                break;
        }

        std::size_t counter = 0;
        for (; iter != _Data.crend(); ++iter) {
            ++counter;
        }
        return counter;
    }

    bool IsZeroTail(const std::size_t aStartPos) const {
        bool res = true;
        if (aStartPos < _Data.size()) {
            std::for_each(_Data.begin() + aStartPos, _Data.end(), [&res](auto& num) {
                res &= (num == 0);
            });
        }
        return res;
    }

    void AddElementInPos(const std::size_t aPos, const byte_t aElement) {
        const std::size_t newSize = aPos + 1;
        if (newSize > _Data.size())
            _Data.resize(newSize);
        _Data[aPos] = aElement;
    }
    
    friend std::ostream& operator<<(std::ostream& aStream, const BigNumber& aBn) {
        if (aBn.RealSize() > sizeof(std::uint64_t)) {
            aStream << "0x";
            auto iter = aBn._Data.crbegin();
            for (; iter != aBn._Data.crend(); ++iter) {
                aStream << boost::str(boost::format("%02X") % ((int)(*iter)));
                if (iter + 1 != aBn._Data.crend())
                    aStream << "\'";
            }
        } 
        else {
            std::uint64_t res = 0;
            for (auto i = 0U; i < aBn.RealSize(); ++i) {
                res |= static_cast<std::uint64_t>(aBn._Data[i]) << (8 * i);
            }
            aStream << res;
        }
        return aStream;
    }
};