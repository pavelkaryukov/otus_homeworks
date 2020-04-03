#pragma once
#include <cstddef>
///\brief Координата объекта на экране
struct TCoord {
    ///\brief Координата объекта на экране
    std::size_t X = 0;
    ///\brief Координата объекта на экране
    std::size_t Y = 0;

    TCoord() = default;
    /**
    * @brief Конструктор TCoord
    * @param aX - положение на оси абсцисс
    * @param aY - положение на оси ординат
    * @return объект TColor
    */
    TCoord(const std::size_t aX, const std::size_t aY) : X(aX), Y(aY) {};
};

