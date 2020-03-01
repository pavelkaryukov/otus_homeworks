#pragma once
#include <cstdint>
#include <string>  
#include <stdlib.h>
#include <tuple>
#include <iostream>
#include "tuple_utils.h"
#include <typeinfo>
//-----------------------------------------------------------------------------
//TODO:: печать адресов длинее 4 байт.
//-----------------------------------------------------------------------------
namespace MyIP
{
    //-----------------------------------------------------------------------------
    enum class ByteOrder
    {
        BigEndian,
        LittleEndian
    };
    //-----------------------------------------------------------------------------
    enum class ErrorCode
    {
        DifferentTypesInTuple,
        NotEnoughData,
        WrongArgument,
        Success
    };
    //-----------------------------------------------------------------------------
    using ConvertResult = std::pair<std::string, ErrorCode>;
    //-----------------------------------------------------------------------------
    template<class T>
    ConvertResult ToStr(const T aBegin, const T aEnd, const ByteOrder aOrder)
    {
        if (aBegin == aEnd)
            return { "", ErrorCode::WrongArgument };

        const auto size = std::distance(aBegin, aEnd);
        std::string res;
        static std::size_t kOneElementStrSize = 4;
        res.reserve(size * kOneElementStrSize);
        auto iter = aBegin;
        while (iter != aEnd) {
            auto insertedPos = [&res, &aOrder]()->std::size_t { return  (aOrder == ByteOrder::BigEndian) ? res.size() : 0; };
            res.insert(insertedPos(), std::to_string(static_cast<std::uint8_t>(*iter)));
            ++iter; 
            if (iter != aEnd) {
                res.insert(insertedPos(), ".");
            }
        }
        return { res, ErrorCode::Success };
    }
    //-----------------------------------------------------------------------------
    template<class T>
    ConvertResult ToStr(const T& aObj, const ByteOrder aOrder = ByteOrder::BigEndian)
    {
        if constexpr (std::is_integral<T>::value) {
            const std::size_t len = sizeof(T);
            auto ptr = (std::uint8_t*)&aObj;
            auto order = (aOrder == ByteOrder::BigEndian) ? ByteOrder::LittleEndian : ByteOrder::BigEndian;
            return ToStr<std::uint8_t*>(ptr, ptr + len, order);
        }
        else {
             auto beginIter =  std::begin(aObj);
             auto endIter   =  std::end(aObj)  ;
             return ToStr<decltype(beginIter)>(beginIter, endIter, aOrder);
        }
    }
    //-----------------------------------------------------------------------------
    ConvertResult ToStr(const std::string aStr, const ByteOrder)
    {
        return { aStr, ErrorCode::Success };
    }
    //-----------------------------------------------------------------------------
    struct ForeachCallback
    {
        ForeachCallback(const std::size_t aMaxIndex, const ByteOrder aOrder = ByteOrder::BigEndian) : m_MaxIndex(aMaxIndex), m_Order(aOrder) {};

        template<std::size_t Index, class T>
        void operator()(T&& element)
        {
            const auto typeName = std::string(typeid(T).name());
            
            if (Index == 0 || m_FirstTupleType.empty())
                m_FirstTupleType = typeName;

            if (m_FirstTupleType != typeName)
                 m_ErrorCode = ErrorCode::DifferentTypesInTuple;

            
            m_Str.insert(InsertedPos(), std::to_string(static_cast<std::uint8_t>(element)));

            if (Index + 1 < m_MaxIndex)
                m_Str.insert(InsertedPos(), ".");;
        }

        ErrorCode   GetErrorCode() const { return m_ErrorCode; };
        std::string GetStr() const { return m_Str; };
    
    private:
        std::string       m_Str;
        const std::size_t m_MaxIndex;
        ErrorCode         m_ErrorCode = ErrorCode::Success;
        const ByteOrder   m_Order;
        std::string       m_FirstTupleType; //Achtung:: Bycicle


        //Methods
        ForeachCallback() = default;
        std::size_t InsertedPos()
        {
            return (m_Order == ByteOrder::BigEndian) ? m_Str.size() : 0;
        }
    };
    //-----------------------------------------------------------------------------
    template<typename...Types>
    ConvertResult ToStr(const std::tuple<Types...> aTuple, const ByteOrder aOrder = ByteOrder::BigEndian) //TODO::добавить порядок байт
    {
        const std::size_t size = std::tuple_size< std::tuple<Types...>>::value;

        auto callback = ForeachCallback(size, aOrder);
        tuple_utils::tupleForeach(callback, aTuple);
        if (callback.GetErrorCode() == ErrorCode::Success)
            return { callback.GetStr(), callback.GetErrorCode() };
        //Проверка на разные типы
        return { "", callback.GetErrorCode() };
    }
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
        case ErrorCode::DifferentTypesInTuple:
            return "Different Types In Tuple > 0xFF\r\n";
        }
    }
    //-----------------------------------------------------------------------------
    void PrintIpAddr(const ConvertResult& aRes)
    {
        if (aRes.second == ErrorCode::Success)
            std::cout << aRes.first << std::endl;
    }

    //-----------------------------------------------------------------------------
}




