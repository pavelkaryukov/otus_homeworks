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
        _Number.clear();
        _Number.insert(_Number.begin(), aVect.crbegin(), aVect.crend());
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
        _Number.clear();
        AddNumber(aNumber);
        return *this;
    }

    void Decrement(const std::size_t aPos) {
        if (aPos >= RealSize())
            throw std::logic_error("BigNumber: method Decrement: negative number");
        if (_Number[aPos] == 0) {
            _Number[aPos] = std::numeric_limits<byte_t>::max();
            Decrement(aPos + 1);
            return;
        }
        _Number[aPos] -= 1;
    }

    BigNumber& operator-=(const BigNumber& aRhs) {
        if (*this < aRhs)
            throw std::logic_error("BigNumber: operator-=: negative number");

        std::size_t len = std::min(RealSize(), aRhs.RealSize());
        for (int i = 0; i < len; ++i) {
            if (_Number[i] < aRhs._Number[i]) {
                auto tmp = aRhs._Number[i] - _Number[i];
                _Number[i] = 0;
                Decrement(i);
                _Number[i] -= tmp;
                ++_Number[i];
                continue;
            }
            _Number[i] -= aRhs._Number[i];
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
            _Number.resize(aRhs.RealSize());

        byte_t tail = 0;
        for (int i = 0; i < aRhs.RealSize(); ++i) {
            std::uint16_t tmp = tail + static_cast<std::uint16_t>(aRhs._Number[i]) + static_cast<std::uint16_t>(_Number[i]);
            _Number[i] = tmp & 0xff;
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
        return (*this + 1U);
    }

    BigNumber& operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const BigNumber& aRhs) const {
        auto minLen = std::min(RealSize(), aRhs.RealSize());
        bool res = std::equal(_Number.begin(), _Number.begin() + minLen, aRhs._Number.begin(), aRhs._Number.begin() + minLen);
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
            if (_Number[index] > aRhs._Number[index])
                return true;
            else if (_Number[index] < aRhs._Number[index])
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
    std::vector<byte_t> _Number = { {0} };

    template<class TNumber, class = typename std::enable_if_t<std::is_integral_v<TNumber>>>
    void AddNumber(const TNumber aNumber) {
        auto len = sizeof(TNumber);
        auto ptr = (byte_t*)(&aNumber);
        AddArray(ptr, len);
    }

    void AddArray(const byte_t* aPtr, std::size_t aLen) {
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

    std::size_t RealSize() const {
        auto iter = _Number.crbegin();
        for (; iter != _Number.crend(); ++iter) {
            if (*iter != 0)
                break;
        }

        std::size_t counter = 0;
        for (; iter != _Number.crend(); ++iter) {
            ++counter;
        }
        return counter;
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

    void AddElementInPos(const std::size_t aPos, const byte_t aElement) {
        const std::size_t newSize = aPos + 1;
        if (newSize > _Number.size())
            _Number.resize(newSize);
        _Number[aPos] = aElement;
    }
    
    friend std::ostream& operator<<(std::ostream& aStream, const BigNumber& aBn) {
        if (aBn.RealSize() > sizeof(std::uint64_t)) {
            aStream << "0x";
            auto iter = aBn._Number.crbegin();
            for (; iter != aBn._Number.crend(); ++iter) {
                aStream << boost::str(boost::format("%02X") % ((int)(*iter)));
                if (iter + 1 != aBn._Number.crend())
                    aStream << "\'";
            }
        } 
        else {
            std::uint64_t res = 0;
            for (int i = 0; i < aBn.RealSize(); ++i) {
                res |= static_cast<std::uint64_t>(aBn._Number[i]) << (8 * i);
            }
            aStream << res;
        }
        return aStream;
    }
};