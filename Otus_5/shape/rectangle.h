#pragma once
#include "shape\ishape.h"
#include <iostream>
///\brief фигура прямоугольник 
struct Rectangle : public IShape {

    Rectangle() = default;

    std::unique_ptr<IShape> Clone() override {
        auto[error, shape] = CreateShape<Rectangle>(this->CoordBegin, this->CoordEnd, this->Thickness, this->Color);
        if ((error == ErrorCode::Succes) && (shape != nullptr)) {
            return std::move(shape);
        }
        return nullptr;
        //throw std::logic_error("The method or operation is not implemented.");
    }

    ErrorCode Paint() override {
        std::cout << "class Rectangle:: method Paint()" << std::endl;
        return ErrorCode::Succes;
    }

    ~Rectangle() {};
};