#include "shape\ishape.h"
#include "shape\rectangle.h"
#include "shape\circle.h"
#include "shape\line.h"
#include <vector>
//¬ –”“»“‹ ÀŒ√√≈–
void TestFigureCreator() {
    std::vector<std::unique_ptr<IShape>>  allShapes;
    
    auto[errorCircle, circle] = CreateShape<Circle>(TCoord(0, 12), TCoord(22, 34), 1, TColor(0xf0, 0xFF, 0x82, 0x34));
    if ((errorCircle == ErrorCode::Succes) && (circle != nullptr)) {
        allShapes.emplace_back(std::move(circle));
    }

    auto[errorLine, line] = CreateShape<Line>(TCoord(10, 78), TCoord(85, 129), 45, TColor(0x23, 0x7a, 0xbc, 0xde));
    if ((errorLine == ErrorCode::Succes) && (line != nullptr)) {
        allShapes.emplace_back(std::move(line));
    }

    auto[errorRectangle, rectangle] = CreateShape<Rectangle>(TCoord(8, 99), TCoord(0xde, 87), 9, TColor(0x23, 0x7a, 0xaa, 0xb2));
    if ((errorRectangle == ErrorCode::Succes) && (rectangle != nullptr)) {
        allShapes.emplace_back(std::move(rectangle));
    }

    for (const auto& shape : allShapes) {
        shape->Paint();
    }

    std::vector<std::unique_ptr<IShape>>  allShapesClones;
    
    for (const auto& shape : allShapes) {
        auto shapeClone = shape->Clone();
        if (shapeClone != nullptr)
            allShapesClones.emplace_back(std::move(shapeClone));
    }

    std::cout << "Test Clones" << std::endl;
    allShapes.insert(allShapes.end(), std::make_move_iterator(allShapesClones.begin()), std::make_move_iterator(allShapesClones.end()));
    
    for (const auto& shape : allShapes) {
        shape->Paint();
    }

}

int main() {
    //std::pair<ErrorCode, std::unique_ptr<T>> CreateShape
    TestFigureCreator();

    int sotp1 = 0;
}