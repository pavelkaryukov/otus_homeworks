#pragma once
#include "error_code/my_error_code.h"
#include "work_space/painter.h"
#include "shape/circle.h"
#include "shape/rectangle.h"
#include "shape/line.h"
#include "file_system/file_manager.h"
#include <optional>
//контролит состояние канваса, художника, файловой системы

//Задумка такая - Application управляется GUI,  и наружу торчит то что в paint торчит
struct Application {
    Application() = default;
    

    ErrorCode AddCircle(const TCoord aBegin, const TCoord aEnd) {
        return AddCircle(aBegin, aEnd, m_Thickness, m_Color);
    }

    ErrorCode AddCircle(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        return GetPainter()->AddShape<Circle>(aBegin, aEnd, aThck, aColor);
    }

    ErrorCode AddLine(const TCoord aBegin, const TCoord aEnd) {
        return AddLine(aBegin, aEnd, m_Thickness, m_Color);
    }

    ErrorCode AddLine(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        return GetPainter()->AddShape<Line>(aBegin, aEnd, aThck, aColor);
    }

    ErrorCode AddRectangle(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        return AddRectangle(aBegin, aEnd, aThck, aColor);
    }

    ErrorCode AddRectangle(const TCoord aBegin, const TCoord aEnd) {
        return GetPainter()->AddShape<Rectangle>(aBegin, aEnd, m_Thickness, m_Color);
    }

    void SetThickness(const IShape::thickens_t aThickness) {
        m_Thickness = aThickness;
    }

    void SetColor(const TColor aColor) {
        m_Color = aColor;
    }

    std::optional<Painter::shapeid_t> SelectShape(const std::size_t aX, const std::size_t aY) {
        //Ткнул мышкой в экра - получил id фигуры  
        return std::nullopt;
    };


    ErrorCode DeleteShape(const std::size_t aID) {
        return GetPainter()->EraseShape(aID);
    }

    ErrorCode DeleteShape(const std::size_t aX, const std::size_t aY) { //
        auto id = SelectShape(aX, aY);
        if (!id)
            return ErrorCode::Error1;
        return DeleteShape(*id);
    }
    
    ErrorCode ResizeCanvas(const std::size_t aX, const std::size_t aY) {
        m_X = aX;
        m_Y = aY;
        return GetPainter()->ResizeCanvas(m_X, m_Y);
    }

    std::pair<std::size_t, std::size_t> GetCanvasSize() {
        return { m_X, m_Y };
    }

#pragma region FileSystemMethods
    //По задумке тут будут вызываться всякие контексные меню выбора файла и тд
    ErrorCode Import() {
        GetPainter()->Clear();
        auto errorCode = m_FileManager.Import(*GetPainter());
        auto res = GetPainter()->GetSize();
        m_X = res.first;
        m_Y = res.second;
        return ErrorCode::Succes;

        //Вызывается окно импорта из класса - MyFileSystem;
        //throw std::logic_error("Method not implemented - ErrorCode Import(IFile* aFile)");
    }

    ErrorCode Export() {
        //Вызывается окно экспорта из класса - MyFileSystem;
        throw std::logic_error("Method not implemented - ErrorCode Export(IFile* aFile)");
    }

    ErrorCode Save() {
        return m_FileManager.Save();
    }
#pragma endregion

private:
    std::size_t              m_X = 800;
    std::size_t              m_Y = 600;
    TColor                   m_Color;
    IShape::thickens_t       m_Thickness;

    std::unique_ptr<Painter> m_Painter;//Один и уникаленю замутим ленивую инициализацию 
    FileManager              m_FileManager;

    
    Painter* GetPainter() {
        if (m_Painter == nullptr) {
            m_Painter = std::make_unique<Painter>(Canvas(m_X, m_Y));
        }
        return m_Painter.get();
    }
    

};