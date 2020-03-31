#pragma once
#include "shape\ishape.h"
#include <iostream>
///\brief фигура прямоугольник 
struct Rectangle : public IShape {

    Rectangle() = default;
    
    Rectangle(
        const TCoord       aCoordBegin,
        const TCoord       aCoordEnd,
        const std::uint8_t aThickness,
        const TColor       aColor
    ) : IShape(aCoordBegin, aCoordEnd, aThickness, aColor) {}

    std::unique_ptr<IShape> Clone(const TCoord aCoordBegin, const TCoord aCoordEnd) override {
        return std::make_unique<Rectangle>(aCoordBegin, aCoordEnd, GetThickness(), GetColor());
    }

    ErrorCode Paint(/*Canvas* aCanvas*/) override {
        std::cout << "class Rectangle:: method Paint(); Canvas: " << 0 << std::endl;
        return ErrorCode::Succes;
    }

    ~Rectangle() {};
};