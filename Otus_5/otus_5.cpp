#include "shape\ishape.h"
#include "shape\rectangle.h"
#include "shape\circle.h"
#include "shape\line.h"
#include <vector>
#include "application/canvas.h"
//¬ –”“»“‹ ÀŒ√√≈–
void TestFigureCreator() {
    std::vector<std::unique_ptr<IShape>>  allShapes;
    
    allShapes.emplace_back(std::make_unique<Circle   >(TCoord(0, 12), TCoord(22, 34), 1, TColor(0xf0, 0xFF, 0x82, 0x34)));
    allShapes.emplace_back(std::make_unique<Line     >(TCoord(10, 78), TCoord(85, 129), 45, TColor(0x23, 0x7a, 0xbc, 0xde)));
    allShapes.emplace_back(std::make_unique<Rectangle>(TCoord(8, 99), TCoord(0xde, 87), 9, TColor(0x23, 0x7a, 0xaa, 0xb2)));

    for (const auto& shape : allShapes) {
        shape->Paint(nullptr);
    }

    std::vector<std::unique_ptr<IShape>>  allShapesClones;
    
    for (const auto& shape : allShapes) {
        auto shapeClone = shape->Clone({}, {});
        if (shapeClone != nullptr)
            allShapesClones.emplace_back(std::move(shapeClone));
    }

    std::cout << "Test Clones" << std::endl;
    allShapes.insert(allShapes.end(), std::make_move_iterator(allShapesClones.begin()), std::make_move_iterator(allShapesClones.end()));
    
    for (const auto& shape : allShapes) {
        shape->Paint(nullptr);
    }
}

void TestCanvas() {
    //std::cout << "Test Canvas\r\n";
    //Canvas canvas;
    //canvas.AddShape(std::make_unique<Circle   >(TCoord(0, 12), TCoord(22, 34), 1, TColor(0xf0, 0xFF, 0x82, 0x34)));
    //canvas.AddShape(std::make_unique<Line     >(TCoord(10, 78), TCoord(85, 129), 45, TColor(0x23, 0x7a, 0xbc, 0xde)));
    //canvas.AddShape(std::make_unique<Rectangle>(TCoord(8, 99), TCoord(0xde, 87), 9, TColor(0x23, 0x7a, 0xaa, 0xb2)));
    //canvas.Clear();


    //int stop1 = 0;


}

int main() {
    //std::pair<ErrorCode, std::unique_ptr<T>> CreateShape
    TestFigureCreator();
    TestCanvas();
    int sotp1 = 0;
}