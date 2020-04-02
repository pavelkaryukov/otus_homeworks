#pragma once
#include "work_space/painter.h"
#include "error_code/my_error_code.h"
#include "shape/circle.h"
#include "shape/rectangle.h"
#include "shape/line.h"
#include "file_system/file_manager.h"
#include <optional>
//контролит состояние канваса, художника, файловой системы

//Задумка такая - Application управляется GUI,  и наружу торчит то что в paint торчит
struct Application {
#pragma region Constructros
    Application() = default;
    Application(
        const std::size_t              aX,
        const std::size_t              aY,
        const TColor                   aColor,
        const IShape::thickens_t       aThickness ) : m_Color(aColor), m_Thickness(aThickness)
    {
        m_Painter = Painter(Canvas(aX, aY));
    }
#pragma endregion

#pragma region ShapeAddingMethods
    ErrorCode AddCircle(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        std::cout << boost::format("Class Application:: method AddCircle\r\n");
        return m_Painter.AddShape<Circle>(aBegin, aEnd, aThck, aColor);
    }

    ErrorCode AddLine(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        std::cout << boost::format("Class Application:: method AddLine\r\n");
        return m_Painter.AddShape<Line>(aBegin, aEnd, aThck, aColor);
    }

    ErrorCode AddRectangle(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        std::cout << boost::format("Class Application:: method AddRectangle\r\n");
        return AddRectangle(aBegin, aEnd, aThck, aColor);
    }

    ErrorCode AddCircle(const TCoord aBegin, const TCoord aEnd) {
        return AddCircle(aBegin, aEnd, m_Thickness, m_Color);
    }

    ErrorCode AddLine(const TCoord aBegin, const TCoord aEnd) {
        return AddLine(aBegin, aEnd, m_Thickness, m_Color);
    }

    ErrorCode AddRectangle(const TCoord aBegin, const TCoord aEnd) {
        return m_Painter.AddShape<Rectangle>(aBegin, aEnd, m_Thickness, m_Color);
    }
#pragma endregion

#pragma region ChangeStateAppMethods
    void SetThickness(const IShape::thickens_t aThickness) {
        std::cout << boost::format("Class Application:: method SetThickness\r\n");
        m_Thickness = aThickness;
    }

    void SetColor(const TColor aColor) {
        std::cout << boost::format("Class Application:: method SetColor\r\n");
        m_Color = aColor;
    }
#pragma endregion

#pragma  region ShapeHandlers
    std::optional<Painter::shapeid_t> SelectShape(const std::size_t aX, const std::size_t aY) {
        //Ткнул мышкой в экра - получил id фигуры  
        return std::nullopt;
    };

    ErrorCode DeleteShape(const std::size_t aID) {
        return m_Painter.EraseShape(aID);
    }

    ErrorCode DeleteShape(const std::size_t aX, const std::size_t aY) { //aX, aY - координаты полученные в результате движения мышкой
        auto id = SelectShape(aX, aY);
        if (!id)
            return ErrorCode::Error1;
        return DeleteShape(*id);
    }
#pragma endregion

#pragma region CanvasHandlers
    ErrorCode ChangeCanvas() {
        //Диалог Смены канваса
        //Вызов ResizeCanvas
        //Вызов ChangeCanvasColor
    }
    
    ErrorCode ResizeCanvas(const std::size_t aX, const std::size_t aY) {
        return m_Painter.ResizeCanvas(aX, aY);
    }
    
    ErrorCode ChangeCanvasColor(const TColor aColor) {
        return m_Painter.ChangeCanvasColor(aColor);
    }

    std::pair<std::size_t, std::size_t> GetCanvasSize() {
        return m_Painter.GetCanvasSize();
    }
#pragma endregion

#pragma region FileSystemMethods
    //По задумке тут будут вызываться всякие контексные меню выбора файла и тд
    ErrorCode Import() {
        m_Painter.Clear();
        auto errorCode = m_FileManager.Import(m_Painter);
        auto res = m_Painter.GetCanvasSize();
//         m_X = res.first;
//         m_Y = res.second;
        return ErrorCode::Succes;

        //Вызывается окно импорта из класса - MyFileSystem;
        //throw std::logic_error("Method not implemented - ErrorCode Import(IFile* aFile)");
    }

    ErrorCode Export() {
        //Вызывается окно экспорта из класса - MyFileSystem;
        return m_FileManager.Export();
    }

    ErrorCode Save() {
        return m_FileManager.Save();
    }
#pragma endregion

private:
    TColor                   m_Color;
    IShape::thickens_t       m_Thickness;
    Painter                  m_Painter = Painter(Canvas(800, 600));//Один и уникаленю замутим ленивую инициализацию 
    FileManager              m_FileManager;
};