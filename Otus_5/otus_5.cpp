#include "shape\ishape.h"
#include "shape\rectangle.h"
#include "shape\circle.h"
#include "shape\line.h"
#include <vector>
#include "work_space/painter.h"
#include "application/application.h"
//¬ –”“»“‹ ÀŒ√√≈–
//void TestFigureCreator() {
//    std::vector<std::unique_ptr<IShape>>  allShapes;
//    
//    allShapes.emplace_back(std::make_unique<Circle   >(TCoord(0, 12), TCoord(22, 34), 1, TColor(0xf0, 0xFF, 0x82, 0x34)));
//    allShapes.emplace_back(std::make_unique<Line     >(TCoord(10, 78), TCoord(85, 129), 45, TColor(0x23, 0x7a, 0xbc, 0xde)));
//    allShapes.emplace_back(std::make_unique<Rectangle>(TCoord(8, 99), TCoord(0xde, 87), 9, TColor(0x23, 0x7a, 0xaa, 0xb2)));
//
//    for (const auto& shape : allShapes) {
//        shape->Paint(nullptr);
//    }
//
//    std::vector<std::unique_ptr<IShape>>  allShapesClones;
//    
//    for (const auto& shape : allShapes) {
//        auto shapeClone = shape->Clone({}, {});
//        if (shapeClone != nullptr)
//            allShapesClones.emplace_back(std::move(shapeClone));
//    }
//
//    std::cout << "Test Clones" << std::endl;
//    allShapes.insert(allShapes.end(), std::make_move_iterator(allShapesClones.begin()), std::make_move_iterator(allShapesClones.end()));
//    
//    for (const auto& shape : allShapes) {
//        shape->Paint(nullptr);
//    }
//    allShapes.clear();
//}
//
void TestPainter() {
    std::cout << "\r\n\r\nTest Canvas\r\n";
    //Application app(new Canvas(800, 600));
    Painter painter(Canvas(1024, 768));
    std::vector<Canvas> testVect;
    testVect.emplace_back(Canvas(1024, 768));
    painter.AddShape<Circle>(TCoord(0, 12), TCoord(22, 34), 1, TColor(0xf0, 0xFF, 0x82, 0x34   ));
    painter.AddShape<Rectangle>(TCoord(10, 78), TCoord(85, 129), 45, TColor(0x23, 0x7a, 0xbc, 0xde));
    painter.AddShape<Line>(TCoord(8, 99), TCoord(0xde, 87), 9, TColor(0x23, 0x7a, 0xaa, 0xb2 ));
    painter.Clear();
}

void TestApplication() {
    Application app;
    app.SetColor(TColor(87, 128, 22, 88));
    app.SetThickness(2);
    app.AddCircle({ 0 , 66  }, { 88, 90 });
    app.AddCircle({ 33, 500 }, { 98, 756});
    app.AddLine  ({ 65, 36  }, { 80, 96 });
    app.SetColor(TColor(85, 66, 1, 82));
    app.SetThickness(15);
    app.AddRectangle({ 0 , 66  }, { 88, 90 });// Â„Ó ‰ÓÎÊÂÌ Û·ËÚ¸
    app.AddRectangle({ 33, 500 }, { 98, 756 });
    app.AddLine     ({ 65, 36  }, { 80, 96 });
    app.DeleteShape(3);
    app.ResizeCanvas(1024, 768);
    app.Export();
    app.Save();
    app.Import();
    
    int stop1 = 0;
}

int main() {
    //std::pair<ErrorCode, std::unique_ptr<T>> CreateShape
    //TestFigureCreator();
    TestApplication();
    int sotp1 = 0;
}