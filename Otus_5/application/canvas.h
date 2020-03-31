#pragma once
#include "shape/ishape.h"
#include "error_code/my_error_code.h"
#include <map>

struct Canvas {
    Canvas() = default;
    Canvas(const std::size_t aX, const std::size_t aY) : X(aX), Y(aY) {};
    ErrorCode Resize(const std::size_t aX, const std::size_t aY) {
        if (false) { // �������������� ����� �� �������, ����� ������ �������� ��� ��� ����� ��
            return ErrorCode::CantResizeCanvas;
        }
        X = aX;
        Y = aY;
        return ErrorCode::Succes;
    }
private:
    std::size_t X = 0;
    std::size_t Y = 0;
};
