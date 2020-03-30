#pragma once
///\brief цвет объекта на экране
struct TColor {
    ///\brief прозрачность пикселя
    std::uint8_t Alpha = 0;
    ///\brief красный цвет пикселя
    std::uint8_t Red = 0;
    ///\brief зеленый цвет пикселя
    std::uint8_t Green = 0;
    ///\brief синия цвет пикселя
    std::uint8_t Blue = 0;

    TColor() = default;

    TColor(const std::uint8_t aAlpha, const std::uint8_t aRed, const std::uint8_t aGreen, const std::uint8_t aBlue) :
        Alpha(aAlpha),
        Red(aRed),
        Green(aGreen),
        Blue(aBlue) {}
};

