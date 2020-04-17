#pragma once       
#include "shape/ishape.h"
#include <iostream>
///\brief фигура Линия, реализует интерфейс IShape
class Line final : public IShape {
public:
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

    CodeResults Paint() override {
        std::cout << boost::format("\x20\x20\x20\Class Line:: method Paint(); Canvas:%1%\r\n") % m_Canvas.get();
        return CodeResults::Succes;
    }

    ~Line() = default;
};
