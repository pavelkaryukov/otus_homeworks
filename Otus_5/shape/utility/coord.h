#pragma once
#include <cstddef>
///\brief ���������� ������� �� ������
struct TCoord {
    ///\brief ���������� ������� �� ������
    std::size_t X = 0;
    ///\brief ���������� ������� �� ������
    std::size_t Y = 0;

    TCoord() = default;
    /**
    * @brief ����������� TCoord
    * @param aX - ��������� �� ��� �������
    * @param aY - ��������� �� ��� �������
    * @return ������ TColor
    */
    TCoord(const std::size_t aX, const std::size_t aY) : X(aX), Y(aY) {};
};

