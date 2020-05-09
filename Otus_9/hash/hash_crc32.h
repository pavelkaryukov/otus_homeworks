#pragma once
#include "hash/ihash.h"
#include <boost/crc.hpp>
#include <boost/format.hpp>
/**
* \brief  ����� ������� ��� ���� �� ��������� CRC32
*/
class HashCRC32 final : public IHash {
public:
    /**
    * \brief �������� ������� ��� ������� ��� ������� (�������� CRC32)
    * \param[in] aData - ��������� �� ������ ������
    * \param[in] aLen - ����� ������� � ������
    */
    void ProcessBuffer(const void* aData, const std::size_t aLen) override {        
        _crc32.process_bytes(aData, aLen);
    }

    /**
    * \brief  �������� ������������ ������ ��� �������
    * \details ���������� ��������� ������ ������� ��� �����
    * \return std::string - ��� ����� �������������� ����� ������
    */
    const std::string Result() override {
        return boost::str(boost::format("[%02X]") % _crc32.checksum());
    }
private:
    boost::crc_32_type  _crc32;
};



