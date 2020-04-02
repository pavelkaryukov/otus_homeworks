#pragma once
#include "shape/ishape.h"
#include <iostream>
///\brief фигура круг 
struct Circle : public IShape {

    Circle() = default;
    Circle(
        std::shared_ptr<Canvas> aCanvas,
        const TCoord       aCoordBegin,
        const TCoord       aCoordEnd,
        const std::uint8_t aThickness,
        const TColor       aColor 
    ) : IShape( aCanvas, aCoordBegin, aCoordEnd, aThickness, aColor) 
    {}


     std::unique_ptr<IShape> Clone(const TCoord aCoordBegin, const TCoord aCoordEnd) override {
         return std::make_unique<Circle>(m_Canvas, aCoordBegin, aCoordEnd, GetThickness(), GetColor());
     }

    ErrorCode Paint() override {
        // Отображать память в 16-ричном виде
        std::cout << "class Circle:: method Paint(); Canvas: " << m_Canvas.get() << std::endl;
        return ErrorCode::Succes;
    }

    ~Circle() {
        int stop1 = 0;
    };

private:
};