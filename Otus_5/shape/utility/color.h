#pragma once
///\brief ���� ������� �� ������
struct TColor {
    ///\brief ������������ �������
    std::uint8_t Alpha = 0;
    ///\brief ������� ���� �������
    std::uint8_t Red = 0;
    ///\brief ������� ���� �������
    std::uint8_t Green = 0;
    ///\brief ����� ���� �������
    std::uint8_t Blue = 0;

    TColor() = default;

    TColor(const std::uint8_t aAlpha, const std::uint8_t aRed, const std::uint8_t aGreen, const std::uint8_t aBlue) :
        Alpha(aAlpha),
        Red(aRed),
        Green(aGreen),
        Blue(aBlue) {}
};

