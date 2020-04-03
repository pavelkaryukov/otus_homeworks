#pragma once
#include "shape/ishape.h"
#include "work_space/canvas.h" 
#include <map>
//Класс художник, хранит в себе все фигуры и отрисовывает их на холств
struct Painter {
    using shapeid_t = std::size_t;
#pragma region Constructors
    Painter() = delete;

    Painter(Canvas&& aCanvas) {
        m_Canvas = std::make_shared<Canvas>(std::move(aCanvas));
        //m_Canvas = std::shared_ptr<Canvas>(new Canvas(std::move(aCanvas)));
    }
#pragma endregion

#pragma region ShapeHandlers
    template<class T>
    ErrorCode AddShape(
        const TCoord       aCoordBegin,
        const TCoord       aCoordEnd,
        const std::uint8_t aThickness,
        const TColor       aColor
    ) {
        static_assert(std::is_base_of<IShape, T>::value);
        auto[iter, res] = m_Shapes.insert({ m_Id.Generate(), std::make_unique<T>(m_Canvas, aCoordBegin, aCoordEnd, aThickness, aColor) });
        if (!res) {
            return ErrorCode::SomeError;
        }
        iter->second->Paint();
        return ErrorCode::Succes;
    }

    //Запуск этого метода предполагается после импорта файла, замены холста и тд и тп
    void PaintAllShapes() {
        for (const auto&[id, shape] : m_Shapes) {
            shape->Paint();
        }
    }

    ErrorCode PaintShape(const shapeid_t aID) {
        auto iter = m_Shapes.find(aID);
        if (iter == m_Shapes.end()) {
            return ErrorCode::SomeError;
        }
        return iter->second->Paint();
    }

    ErrorCode EraseShape(const shapeid_t aID) {
        auto iter = m_Shapes.find(aID);
        if (iter == m_Shapes.end()) {
            return ErrorCode::SomeError;
        }
        m_Shapes.erase(iter);
        return ErrorCode::Succes;
    }
#pragma endregion

#pragma region ChangeStatePainterMethods
    void Clear() {
        m_Id.Clear();
        m_Shapes.clear();
        m_Canvas->Clear();
    }
#pragma endregion

#pragma region CanvasHandlers
    ErrorCode ResizeCanvas(const std::size_t aX, const std::size_t aY) {
        std::cout << "Painter: Resize Canvas\r\n";
        auto res = m_Canvas->Resize(aX, aY);
        if (res != ErrorCode::Succes)
            return res;
        PaintAllShapes();
        return ErrorCode::Succes;
    }

    ErrorCode ChangeCanvasColor(const TColor aColor) {
        std::cout << "Painter: Resize Canvas\r\n";//Фигуры перерисовывать не надо
        auto res = m_Canvas->ChangeColor(aColor);
        if (res != ErrorCode::Succes)
            return res;
        return ErrorCode::Succes;
    }
    
    ErrorCode ChangeCanvas(std::unique_ptr<Canvas> aCanvas) {
        m_Canvas = std::move(aCanvas);
        return ErrorCode::Succes;
    }

    std::pair<std::size_t, std::size_t> GetCanvasSize() const{
        return m_Canvas->GetSize();
    }
#pragma endregion

private:
    std::map<std::size_t, std::unique_ptr<IShape>> m_Shapes;
    std::shared_ptr<Canvas>                        m_Canvas;

#pragma region GeneratorID
    struct IdGenerator {
        shapeid_t Generate() {
            return m_ShapeCounter++;
        }

        void Clear() {
            m_ShapeCounter = 0;
        }

        IdGenerator() = default;
    private:
        shapeid_t m_ShapeCounter = 0;
    };

    IdGenerator m_Id;
#pragma endregion
};

