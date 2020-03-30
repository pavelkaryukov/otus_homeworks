#pragma once
///\brief ���������� ������� �� ������
struct TCoord {
    ///\brief ���������� ������� �� ������
    std::size_t X = 0;
    ///\brief ���������� ������� �� ������
    std::size_t Y = 0;

    TCoord() = default;
    TCoord(const std::size_t aX, const std::size_t aY) : X(aX), Y(aY) {};
};

