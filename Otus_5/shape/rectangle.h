#pragma once
#include "shape/ishape.h"
#include <iostream>
///\brief фигура прямоугольник, реализует интерфейс IShape 
struct Rectangle : public IShape {
    Rectangle() = default;
    
    Rectangle(
        std::shared_ptr<Canvas> aCanvas,
        const TCoord       aCoordBegin,
        const TCoord       aCoordEnd,
        const std::uint8_t aThickness,
        const TColor       aColor
    ) : IShape(aCanvas, aCoordBegin, aCoordEnd, aThickness, aColor) {}

    std::unique_ptr<IShape> Clone(const TCoord aCoordBegin, const TCoord aCoordEnd) override {
        return std::make_unique<Rectangle>(m_Canvas, aCoordBegin, aCoordEnd, GetThickness(), GetColor());
    }

    ErrorCode Paint() override {
        std::cout << boost::format("\x20\x20\x20\Class Rectangle:: method Paint(); Canvas:%1%\r\n") % m_Canvas.get();
        return ErrorCode::Succes;
    }

    ~Rectangle() {};
};