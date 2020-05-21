#pragma once
#include "hash/ihash.h"             
#include <boost/format.hpp>
#include <boost/uuid/detail/md5.hpp>
/**
* \brief  класс расчета хэш сумм по алгоритму MD5
*/
class HashMD5 final : public IHash {
public:
    /**
    * \brief итерация расчета хэш функции для буффера (алгоритм MD5)
    * \param[in] aData - указатель на начало буфера
    * \param[in] aLen - длина буффера в байтах
    */   
    void ProcessBuffer(const void* aData, const std::size_t aLen) override {
        _hash.process_bytes(aData, aLen);
    }

    /**
     * \brief  Получить рассчитанную раньше хэш функцию
     * \details возвращает результат общего расчета хэш суммы
     * \return std::string - хэш сумма представляется ввиде строки
     */
    const std::string Result() override {
        _hash.get_digest(_digest);
        std::string res;
        for (auto& elem : _digest) {
            res += boost::str(boost::format("[%02X]") % elem);
        }
        return res;
    }
private:
    boost::uuids::detail::md5 _hash;
    boost::uuids::detail::md5::digest_type _digest;
};

