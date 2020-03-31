#pragma once
#include "shape/ishape.h"
#include <map>
#include <vector>    
//struct Canvas {};

struct IdGenerator {
    
    std::size_t Generate() {
        return m_ShapeCounter++;
    }

    void Clear() {
        m_ShapeCounter = 0;
    }

    IdGenerator() = default;

private:
    std::size_t m_ShapeCounter = 0;
};
//
struct Canvas {

    //ErrorCode AddShape(std::unique_ptr<IShape> aShape) {
    //    //Отрисуем фигуру на холсте, если все удачно - то разместим её в mape
    //    if (aShape->Paint(this) != ErrorCode::Succes)
    //        return ErrorCode::CantPaintShapeOnCanvas;
    //    m_Shapes[m_IdGenerator.Generate()] = std::move(aShape);
    //    return ErrorCode::Succes;
    //}

    //void Clear() {
    //    m_IdGenerator.Clear();
    //    m_Shapes.clear();
    //}

    ////Запуск этого метода предполагается после импорта файла
    //void PaintAllShapes() {
    //    for (const auto& [id, shape] : m_Shapes) {
    //        shape->Paint(this);
    //    }
    //}

private:

    IdGenerator m_IdGenerator;

    //std::vector<std::unique_ptr<IShape>>  allShapes;
    //std::vector<std::unique_ptr<IShape>> m_Shapes;
    std::map<std::size_t, std::unique_ptr<IShape>> m_Shapes;

};
//