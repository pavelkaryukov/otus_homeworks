#pragma once
#include <cstdint>
#include <string>  
#include <stdlib.h>
//-----------------------------------------------------------------------------
namespace MyIPv4
{
    //-----------------------------------------------------------------------------
    enum class ByteOrder
    {
        BigEndian,
        LittleEndian
    };
    //-----------------------------------------------------------------------------
    const std::size_t kMinSize = 4;
    //-----------------------------------------------------------------------------
    enum class ErrorCode
    {
        NotEnoughData,
        NullArgument,
        WrongArgument,
        MoreMaxByteValue,
        Success
    };
    using ConvertResult = std::pair<std::string, ErrorCode>;
    //-----------------------------------------------------------------------------
    template<class T>
    ConvertResult ToStr(const T aBegin, const T aEnd, const ByteOrder aOrder)
    {
        if (aBegin > aEnd)
            return { "", ErrorCode::WrongArgument };
        if (std::distance(aBegin, aEnd) < kMinSize)
            return  { "", ErrorCode::NotEnoughData };
        std::string res;
        res.reserve(kMinSize * 5);
        auto iter = aBegin;
        while ((iter < aBegin + kMinSize) && (aBegin != aEnd)) {
            if (*iter > 0xff)
                return { "", ErrorCode::MoreMaxByteValue };
            auto insertedPos = [&res, &aOrder]()->std::size_t { return  (aOrder == ByteOrder::BigEndian) ? res.size() : 0; };
            res.insert(insertedPos(), std::to_string(static_cast<std::uint8_t>(*iter)));
            ++iter; 
            if (iter < aBegin + kMinSize) {
                res.insert(insertedPos(), ".");
            }
        }
        return { res, ErrorCode::Success };
    }
    //-----------------------------------------------------------------------------
    template<class T>
    ConvertResult ToStr(const T& aObj, const ByteOrder aOrder = ByteOrder::BigEndian) //TODO::добавить порядок байт
    {
        if constexpr (std::is_integral<T>::value) {
             if (sizeof(aObj) < kMinSize)
                 return { "", ErrorCode::NotEnoughData };
            auto ipv4 = *(std::uint32_t*)&aObj;
            ipv4 = _byteswap_ulong(ipv4);
            auto ptr = (std::uint8_t*)&ipv4;
            return ToStr(ptr, ptr + kMinSize, aOrder);
        }
        else {
             auto beginIter =  std::begin(aObj);
             auto endIter   =  std::end(aObj)  ;
             return ToStr(beginIter, endIter, aOrder);
        }
    }
    //-----------------------------------------------------------------------------
//     ConvertResult ToStr(std::string aStr, const ByteOrder aOrder = ByteOrder::BigEndian) //TODO::добавить порядок байт
//     {
//         //if ()
//     }
    //-----------------------------------------------------------------------------
    std::string ErrorCodeToStr(const ErrorCode aCode)
    {
        //English from Hell
        switch (aCode) {
        default:
            return "Unknown error code\r\n";
        case ErrorCode::NotEnoughData:
            return "Not enough data (container/type size < 4 elements/bytes)\r\n";
        case ErrorCode::Success:
            return "Convert to str was corrected\r\n";
        case ErrorCode::WrongArgument:
            return "Wrong argument\r\n";
        case ErrorCode::MoreMaxByteValue:
            return "One Element > 0xFF\r\n";
        }
    }
    //-----------------------------------------------------------------------------
}




