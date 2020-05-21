#pragma once
#include "hash/ihash.h"
#include <boost/crc.hpp>
#include <boost/format.hpp>
/**
* \brief  класс расчета хэш сумм по алгоритму CRC32
*/
class HashCRC32 final : public IHash {
public:
    /**
    * \brief итерация расчета хэш функции для буффера (алгоритм CRC32)
    * \param[in] aData - указатель на начало буфера
    * \param[in] aLen - длина буффера в байтах
    */
    void ProcessBuffer(const void* aData, const std::size_t aLen) override {        
        _crc32.process_bytes(aData, aLen);
    }

    /**
    * \brief  Получить рассчитанную раньше хэш функцию
    * \details возвращает результат общего расчета хэш суммы
    * \return std::string - хэш сумма представляется ввиде строки
    */
    const std::string Result() override {
        return boost::str(boost::format("[%02X]") % _crc32.checksum());
    }
private:
    boost::crc_32_type  _crc32;
};



