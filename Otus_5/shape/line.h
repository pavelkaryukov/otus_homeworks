#pragma once       
#include "shape\ishape.h"
#include <iostream>
///\brief фигура круг
struct Line : public IShape {

    Line() = default;

    std::unique_ptr<IShape> Clone() override {
        auto[error, shape] = CreateShape<Line>(this->CoordBegin, this->CoordEnd, this->Thickness, this->Color);
        if ((error == ErrorCode::Succes) && (shape != nullptr)) {
            return std::move(shape);
        }
        return nullptr;
    }

    ErrorCode Paint() override {
        std::cout << "class Line:: method Paint()" << std::endl;
        return ErrorCode::Succes;
    }

    ~Line() {};
};
