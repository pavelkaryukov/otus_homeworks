#pragma once
#include "shape/ishape.h"
#include "error_code/my_error_code.h"
#include <map>

struct Canvas {
    Canvas() = default;
    Canvas(const std::size_t aX, const std::size_t aY) : m_X(aX), m_Y(aY) {};

    ErrorCode Resize(const std::size_t aX, const std::size_t aY) {
        if (Clear() != ErrorCode::Succes) { // предполагается какое то условие, холст больше монитора или ещё какой ад
            return ErrorCode::CantResizeCanvas;
        }
        m_X = aX;
        m_Y = aY;
        return ErrorCode::Succes;
    }

    ErrorCode Clear() {
        //Стирает все с холста
        return ErrorCode::Succes;
    }

    ErrorCode ChangeColor(const TColor aColor) {
        m_Color = aColor;
        return ErrorCode::Succes;
    }

    std::pair<std::size_t, std::size_t> GetSize() {
        return { m_X, m_Y };
    }

private:
    std::size_t m_X = 0;
    std::size_t m_Y = 0;
    TColor      m_Color;
};