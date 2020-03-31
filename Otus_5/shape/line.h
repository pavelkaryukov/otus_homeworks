#pragma once       
#include "shape\ishape.h"
#include <iostream>
///\brief фигура круг
struct Line : public IShape {

    Line() = default;
    
    Line(
        const TCoord       aCoordBegin,
        const TCoord       aCoordEnd,
        const std::uint8_t aThickness,
        const TColor       aColor
    ) : IShape(aCoordBegin, aCoordEnd, aThickness, aColor) {}

    std::unique_ptr<IShape> Clone(const TCoord aCoordBegin, const TCoord aCoordEnd) override {
        return std::make_unique<Line>(aCoordBegin, aCoordEnd, GetThickness(), GetColor());
    }

    ErrorCode Paint(Canvas* aCanvas) override {
        std::cout << "class Line:: method Paint(); Canvas: " << aCanvas << std::endl;
        return ErrorCode::Succes;
    }

    ~Line() {};
};
