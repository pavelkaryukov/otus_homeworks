#pragma once
#include "hash/ihash.h"             
#include <boost/format.hpp>
#include <boost/uuid/detail/md5.hpp>
/**
* \brief  ����� ������� ��� ���� �� ��������� MD5
*/
class HashMD5 final : public IHash {
public:
    /**
    * \brief �������� ������� ��� ������� ��� ������� (�������� MD5)
    * \param[in] aData - ��������� �� ������ ������
    * \param[in] aLen - ����� ������� � ������
    */   
    void ProcessBuffer(const void* aData, const std::size_t aLen) override {
        _hash.process_bytes(aData, aLen);
    }

    /**
     * \brief  �������� ������������ ������ ��� �������
     * \details ���������� ��������� ������ ������� ��� �����
     * \return std::string - ��� ����� �������������� ����� ������
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

