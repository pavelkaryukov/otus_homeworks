#pragma once
#include "error_code/my_error_code.h"
#include "application/painter.h"
#include "shape/circle.h"
#include "shape/rectangle.h"
#include "shape/line.h"
#include <optional>

struct IFile {

};

//Задумка такая - Application управляется GUI,  и наружу торчит то что в paint торчит
struct Application {
    Application() = default;
    ErrorCode Import(IFile* aFile);
    ErrorCode Export(IFile* aFile);
    
    ErrorCode AddCircle(const TCoord aBegin, const TCoord aEnd) {
        GetPainter()->AddShape<Circle>(aBegin, aEnd, m_Thickness, m_Color);
    }

    ErrorCode AddLine(const TCoord aBegin, const TCoord aEnd) {
        GetPainter()->AddShape<Line>(aBegin, aEnd, m_Thickness, m_Color);
    }

    ErrorCode AddRectangle(const TCoord aBegin, const TCoord aEnd) {
        GetPainter()->AddShape<Rectangle>(aBegin, aEnd, m_Thickness, m_Color);
    }

    void SetThickness(const IShape::thickens_t aThickness) {
        m_Thickness = aThickness;
    }

    void SetColor(const TColor aColor) {
        m_Color = aColor;
    }

    std::optional<Painter::shapeid_t> SelectShape(const std::size_t aX, const std::size_t aY) {
        //Ткнул мышкой в экран - получил id фигуры  
        return std::nullopt;
    };


    explicit ErrorCode DeleteShape(const std::size_t aID) {
        GetPainter()->EraseShape(aID);
    }

    explicit ErrorCode DeleteShape(const std::size_t aX, const std::size_t aY) { //
        auto id = SelectShape(aX, aY);
        if (!id)
            return ErrorCode::Error1;
        return DeleteShape(*id);
    }
    
    Painter* GetPainter() {
        if (m_Painter == nullptr) {
            m_Painter = std::make_unique<Painter>(Canvas(X, Y));
        }
        return m_Painter.get();
    }

private:
    std::size_t X = 800;
    std::size_t Y = 600;


    std::unique_ptr<Painter> m_Painter;//Один и уникаленю замутим ленивую инициализацию 
    
    

    IShape::thickens_t m_Thickness;
    TColor m_Color;

};