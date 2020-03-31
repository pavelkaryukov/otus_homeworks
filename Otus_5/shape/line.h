#pragma once       
#include "shape\ishape.h"
#include <iostream>
///\brief фигура круг
struct Line : public IShape {

    Line() = default;
    
    Line(
        std::shared_ptr<Canvas> aCanvas,
        const TCoord       aCoordBegin,
        const TCoord       aCoordEnd,
        const std::uint8_t aThickness,
        const TColor       aColor
    ) : IShape(aCanvas, aCoordBegin, aCoordEnd, aThickness, aColor) {}

     std::unique_ptr<IShape> Clone(const TCoord aCoordBegin, const TCoord aCoordEnd) override {
         return std::make_unique<Line>(m_Canvas, aCoordBegin, aCoordEnd, GetThickness(), GetColor());
     }

    ErrorCode Paint() override {
        std::cout << "class Line:: method Paint(); Canvas: " << m_Canvas.get() << std::endl;
        return ErrorCode::Succes;
    }

    ~Line() {};

private:
};
