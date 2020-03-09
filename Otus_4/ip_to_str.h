#pragma once
#include "tuple_utils.h"
#include <cstdint>
#include <string>  
#include <stdlib.h>
#include <tuple>
#include <iostream>
#include <typeinfo>
/*! \mainpage Otus_4 (Print_IP)
 *
 * link: https://otus.ru/media-private/5c/4e/04_homework-12995-5c4ebc.pdf?hash=JvrtYNNSngfx3plRVe-kPg&expires=1583690347
 * \r\n���������� ������� ������ ��������� IP ������ 
 *
 */
///\brief �������  ������ IPv4 Style
namespace MyIP
{
    /**
    * \enum ByteOrder
    * \brief ������� ���� ��� ����������� � ip ������
    */
    enum class ByteOrder
    {
        /** 
        * \brief ������� ���� - ������� �������
        */
        BigEndian,
        /**
        * \brief ������� ���� - ������� ������� 
        */
        LittleEndian
    };
    /**
    * \enum ErrorCode
    * \brief ��� ������ ������������ �������� ToStr
    */
    enum class ErrorCode
    {
        /**
        * \brief Different Types In Tuple
        */
        DifferentTypesInTuple,
        /**
        * \brief Different Types In Tuple
        */
        NotEnoughData,
        /**
        * \brief Not enough data (container/type size < 4 elements/bytes)
        */
        WrongArgument,
        /**
        * \brief Wrong argument
        */
        Success
    };
    ///\brief ��������� ������� � ���������
    namespace PrivateIP
    {
        /**
        * \brief ��� ����������� � ������ ������������������ ����� ��������, ����� ��� �������������� ������ ��� ������
        */
        std::size_t kOneElementStrSize = 4;
        /**
        * \brief � ����������� �� ������� ����, ���������� ����� ������� � ������
        * \param[in] aStr ������ � ������� ����� ������������� �������     
        * \param[in] aOrder ������� ���� (little endian - big endian)
        * \return  std::size_t  ������� �������
        */
        std::size_t InsertedPos(const std::string& aStr, const ByteOrder aOrder)
        {
            return (aOrder == ByteOrder::BigEndian) ? aStr.size() : 0;
        }
        //������� � http://coliru.stacked-crooked.com/a/a5d838b098495d9f
        ///\brief ���������� ����� �� ������ ��������
        template <typename T, typename = void>
        struct is_iterable : std::false_type {};
        // this gets used only when we can call std::begin() and std::end() on that type
        template <typename T>
        struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>())), decltype(std::end(std::declval<T>()))>> : std::true_type {};
        // Here is a helper:
        template <typename T>
        constexpr bool is_iterable_v = is_iterable<T>::value;
    }
    ///\brief ������������ ��������� ������� ToStr, ���� ������ + ��� ������
    using ConvertResult = std::pair<std::string, ErrorCode>;
    /**
    * \brief ������� ������ ip ������, �������� ����� ���������� '.', ������� ���� ����� ��������
    * \param[in] aBegin ��������� (��������) �� ������
    * \param[in] aEnd ��������� (��������) �� �����  
    * \param[in] aOrder ������� ���� (little endian - big endian)
    * \return  ConvertResult = std::pair<std::string, ErrorCode> ���
    * \return  std::string  ��������� ������������� ip ������
    * \return  ErrorCode  ��� ������
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
    /**
    * \brief ������� ������ ip ������, �������� ����� ���������� '.', ������� ���� ����� ��������
    * \param[in] aObj ������ ���������
    * \param[in] aOrder ������� ���� (little endian - big endian)
    * \return  ConvertResult = std::pair<std::string, ErrorCode> ���
    * \return  std::string  ��������� ������������� ip ������
    * \return  ErrorCode  ��� ������
    */
    template <class TContainer>
    typename std::enable_if<PrivateIP::is_iterable_v<TContainer>, ConvertResult>::type ToStr(const TContainer& aObj, const ByteOrder aOrder = ByteOrder::BigEndian)
    {
        auto beginIter = std::begin(aObj);
        auto endIter = std::end(aObj);
        return ToStr<decltype(beginIter)>(beginIter, endIter, aOrder);
    }
    /**
    * \brief ������� ������ ip ������, �������� ����� ���������� '.', ������� ���� ����� ��������
    * \param[in] aObj ������ ������������� ����
    * \param[in] aOrder ������� ���� (little endian - big endian)
    * \return  ConvertResult = std::pair<std::string, ErrorCode> ���
    * \return  std::string  ��������� ������������� ip ������
    * \return  ErrorCode  ��� ������
    */
    template<class T>
    typename std::enable_if<std::is_integral_v<T>, ConvertResult>::type ToStr(const T& aObj, const ByteOrder aOrder = ByteOrder::BigEndian)
    {
         const std::size_t len = sizeof(T);
         auto ptr = (std::uint8_t*)&aObj;
         auto order = (aOrder == ByteOrder::BigEndian) ? ByteOrder::LittleEndian : ByteOrder::BigEndian;
         return ToStr<std::uint8_t*>(ptr, ptr + len, order);
     }
    /**
    * \brief ������� ������ ip ������, �������� ����� ���������� '.', ������� ���� ����� ��������
    * \param[in] aStr ������, ������� ����� ����������
    * \return  ConvertResult = std::pair<std::string, ErrorCode> ���
    * \return  std::string  ��������� ������������� ip ������
    * \return  ErrorCode  ��� ������
    */
    ConvertResult ToStr(const std::string aStr, const ByteOrder)
    {
        return { aStr, ErrorCode::Success };
    }
    /**
    * \brief ������� ������ ip ������, �������� ����� ���������� '.', ������� ���� ����� ��������
    * \param[in] aTuple ������ Tuple
    * \param[in] aOrder ������� ���� (little endian - big endian)
    * \return  ConvertResult = std::pair<std::string, ErrorCode> ���
    * \return  std::string  ��������� ������������� ip ������
    * \return  ErrorCode  ��� ������
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
    /**
    * \brief ������� ������ �� ����� ������ ���� ������
    * \param[in] aCode ��� ������ 
    */
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
    /**
    * \brief ������� ������ �� ����� ip ������, ��������� � ���������� ������ ������� ToStr
    * \param[in] aRes ��������� ��������� ������� ToStr
    */
    void PrintIpAddr(const ConvertResult& aRes)
    {
        if (aRes.second == ErrorCode::Success)
            std::cout << aRes.first << std::endl;
    }
}




