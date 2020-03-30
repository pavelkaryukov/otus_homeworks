#pragma once
#include "shape\ishape.h"
#include <iostream>
///\brief фигура круг 
struct Circle : public IShape {

    Circle() = default;

    std::unique_ptr<IShape> Clone() override {
        auto[error, shape] = CreateShape<Circle>(this->CoordBegin, this->CoordEnd, this->Thickness, this->Color);
        if ((error == ErrorCode::Succes) && (shape != nullptr)) {
            return std::move(shape);
        }
        return nullptr;
    }


    ErrorCode Paint() override {
        std::cout << "class Circle:: method Paint()" << std::endl;
        return ErrorCode::Succes;
    }

    ~Circle() {};
};