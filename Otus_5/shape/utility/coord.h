#pragma once
///\brief Координата объекта на экране
struct TCoord {
    ///\brief Координата объекта на экране
    std::size_t X = 0;
    ///\brief Координата объекта на экране
    std::size_t Y = 0;

    TCoord() = default;
    TCoord(const std::size_t aX, const std::size_t aY) : X(aX), Y(aY) {};
};

