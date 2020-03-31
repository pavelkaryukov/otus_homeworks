#pragma once
#include "shape/ishape.h"
#include <map>

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

struct Canvas {

    ErrorCode AddShape(std::unique_ptr<IShape> aShape) {
        //Отрисуем фигуру на холсте, если все удачно - то разместим её в mape
        if (aShape->Paint() != ErrorCode::Succes)
            return ErrorCode::CantPaintShapeOnCanvas;
        m_Shapes[m_Id.Generate()] = std::move(aShape);
        return ErrorCode::Succes;
    }

    void Clear() {
        m_Id.Clear();
        m_Shapes.clear();
    }

    //Запуск этого метода предполагается после импорта файла
    void PaintAllShapes() {
        for (const auto& [id, shape] : m_Shapes) {
            shape->Paint();
        }
    }

private:

    IdGenerator m_Id;

    std::map<std::size_t, std::unique_ptr<IShape>> m_Shapes;

};
