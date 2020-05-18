#pragma once
#include <cctype>
#include <iostream>
/*! \mainpage Otus_11 (BulkMT_ASYNC)
 *
 * \r\n  ��������� ����� (������������� �����������)
 *
 */
namespace async {
    using handle_t = std::uint64_t;

    /**
    * \brief  �������� ����������� ������
    * \param[in] bulk - ���-�� ������ � ����
    * \param[in] aOutStream - ����� ������ ����
    * \return id ����������� (���� 0 - �� ������ �� ������)
    */
    handle_t connect(std::size_t bulk, std::ostream& aOutStream = std::cout);

    /**
    * \brief  ��������� �������
    * \param[in] handle - id �����������
    * \param[in] data - ��������� �� ������ �������
    * \param[in] size - ������ �������
    */
    void receive(handle_t handle, const char *data, std::size_t size);

    /**
    * \brief  ����������� �����������
    * \param[in] handle - id �����������
    */
    void disconnect(handle_t handle);
}