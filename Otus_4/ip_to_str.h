#pragma once
#include <cstdint>
#include <string>  
#include <stdlib.h>
#include <tuple>
#include <iostream>
#include "tuple_utils.h"
#include <typeinfo>
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
    namespace PrivateIP
    {
        std::size_t kOneElementStrSize = 4;
        //-----------------------------------------------------------------------------
        std::size_t InsertedPos(const std::string& aStr, const ByteOrder aOrder)
        {
            return (aOrder == ByteOrder::BigEndian) ? aStr.size() : 0;
        }
    }
    //-----------------------------------------------------------------------------
    using ConvertResult = std::pair<std::string, ErrorCode>;
    //-----------------------------------------------------------------------------
    /**
     * @brief ������� ������ ip ������, �������� ����� ���������� '.', ������� ���� ����� ��������
     * @param[in] aBegin ��������� (��������) �� ������
     * @param[in] aEnd ��������� (��������) �� �����  
     * @param[in] aOrder ������� ���� (little endian - big endian)
     * @return  ConvertResult = std::pair<std::string, ErrorCode> ���
     * @return  std::string  ��������� ������������� ip ������
     * @return  ErrorCode  ��� ������
     */
    template<class T>
    ConvertResult ToStr(const T aBegin, const T aEnd, const ByteOrder aOrder)
    {
        if (aBegin == aEnd)
            return { "", ErrorCode::WrongArgument };

        const auto size = std::distance(aBegin, aEnd);
        std::string res;
        res.reserve(size * PrivateIP::kOneElementStrSize);
        auto iter = aBegin;
        while (iter != aEnd) {
            auto insertedPos = [&res, &aOrder]()->std::size_t { return  (aOrder == ByteOrder::BigEndian) ? res.size() : 0; };
            res.insert(insertedPos(), std::to_string(static_cast<std::size_t>(*iter)));
            ++iter; 
            if (iter != aEnd) {
                res.insert(insertedPos(), ".");
            }
        }
        return { res, ErrorCode::Success };
    }
    //-----------------------------------------------------------------------------
    /**
     * @brief ������� ������ ip ������, �������� ����� ���������� '.', ������� ���� ����� ��������
     * @param[in] aObj ������ ������������� ���� ��� �� ��������� � ��������� ����������
     * @param[in] aOrder ������� ���� (little endian - big endian)
     * @return  ConvertResult = std::pair<std::string, ErrorCode> ���
     * @return  std::string  ��������� ������������� ip ������
     * @return  ErrorCode  ��� ������
     */
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
     /**
     * @brief ������� ������ ip ������, �������� ����� ���������� '.', ������� ���� ����� ��������
     * @param[in] aStr ������, ������� ����� ����������
     * @return  ConvertResult = std::pair<std::string, ErrorCode> ���
     * @return  std::string  ��������� ������������� ip ������
     * @return  ErrorCode  ��� ������
     */
    ConvertResult ToStr(const std::string aStr, const ByteOrder)
    {
        return { aStr, ErrorCode::Success };
    }
    //-----------------------------------------------------------------------------
    /**
    * @brief ������� ������ ip ������, �������� ����� ���������� '.', ������� ���� ����� ��������
    * @param[in] aStr ������, ������� ����� ����������
    * @return  ConvertResult = std::pair<std::string, ErrorCode> ���
    * @return  std::string  ��������� ������������� ip ������
    * @return  ErrorCode  ��� ������
    */
    template<typename...Types>
    ConvertResult ToStr(const std::tuple<Types...> aTuple, const ByteOrder aOrder = ByteOrder::BigEndian) //TODO::�������� ������� ����
    {
        const std::size_t size = std::tuple_size< std::tuple<Types...>>::value;
        std::string resStr;
        resStr.reserve(size * PrivateIP::kOneElementStrSize);
        auto errorCode = ErrorCode::Success;
        std::size_t index = 0;

        tuple_utils::for_each(aTuple,
            [&](auto&& e)
        { 
            if (typeid(e) != typeid(std::get<0>(aTuple)))
                errorCode = ErrorCode::DifferentTypesInTuple;

            resStr.insert(PrivateIP::InsertedPos(resStr, aOrder), std::to_string(static_cast<std::uint8_t>(e)));
            ++index;
            if (index < size)
                resStr.insert(PrivateIP::InsertedPos(resStr, aOrder), ".");
        }
        );
        
        if (errorCode != ErrorCode::Success)
            resStr.clear();

        return { resStr, errorCode };
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
    /**
    * @brief ������� ������ �� ����� ip ������, ��������� � ���������� ������ ������� ToStr
    * @param[in] ConvertResult ��������� ��������� ������� ToStr
    */
    void PrintIpAddr(const ConvertResult& aRes)
    {
        if (aRes.second == ErrorCode::Success)
            std::cout << aRes.first << std::endl;
    }
    //-----------------------------------------------------------------------------
}




