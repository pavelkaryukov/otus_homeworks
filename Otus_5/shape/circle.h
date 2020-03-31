#pragma once
#include "shape\ishape.h"
#include <iostream>
///\brief фигура круг 
struct Circle : public IShape {

    Circle() = default;
    Circle(
        const TCoord       aCoordBegin,
        const TCoord       aCoordEnd,
        const std::uint8_t aThickness,
        const TColor       aColor 
    ) : IShape( aCoordBegin, aCoordEnd, aThickness, aColor) 
    {}


    std::unique_ptr<IShape> Clone(const TCoord aCoordBegin, const TCoord aCoordEnd) override {
        return std::make_unique<Circle>(aCoordBegin, aCoordEnd, GetThickness(), GetColor());
    }

    ErrorCode Paint(Canvas* aCanvas) override {
        // Отображать память в 16-ричном виде
        std::cout << "class Circle:: method Paint(); Canvas: " << aCanvas << std::endl;
        return ErrorCode::Succes;
    }

    ~Circle() {
        int stop1 = 0;
    };

private:
    ErrorCode Erase() override {
        std::cout << "class Circle:: method Erase(); Canvas: " << 0 << std::endl; 
        return ErrorCode::Succes;
    }
};