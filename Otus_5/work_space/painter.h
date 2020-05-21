#pragma once
#include "shape/ishape.h"
#include "work_space/canvas.h" 
#include <map>

/**
* \brief класс Painter (маляр)
* \details Класс Маляр, хранит в себе все фигуры и отрисовывает их на холств
*/
class Painter final {
public:
    using shapeid_t = std::size_t;
#pragma region Constructors

    /**
    * \brief Конструктор класса Painter
    * \param[in] aCanvas rvalue Canvas - холс
    * \details создает объект класса маляр
    * \return  объект класса Painter
    */
    Painter(Canvas&& aCanvas) {
        m_Canvas = std::make_shared<Canvas>(std::move(aCanvas));
    }
#pragma endregion

#pragma region ShapeHandlers
    /**
    * \brief Добавляет фигуру и отрисовывает на холсте
    * \param[in] aCoordBegin координата начала фигуры
    * \param[in] aCoordEnd координата конца фигуры
    * \param[in] aThickness ширина линии фигуры
    * \param[in] aColor цвет фигуры - ARGB
    * \details Добавляет фигуру  в m_Shapes и отрисовывает на холсте
    * \return CodeResults код ошибки
    */
    template<class T>
    CodeResults AddShape(
        const TCoord       aCoordBegin,
        const TCoord       aCoordEnd,
        const std::uint8_t aThickness,
        const TColor       aColor
    ) {
        static_assert(std::is_base_of<IShape, T>::value);
        auto[iter, res] = m_Shapes.insert({ m_Id.Generate(), std::make_unique<T>(m_Canvas, aCoordBegin, aCoordEnd, aThickness, aColor) });
        if (!res) {
            return CodeResults::SomeError;
        }
        iter->second->Paint();
        return CodeResults::Succes;
    }

    /**
    * \brief Отрисовывает все фигуры на холсте
    */
    void PaintAllShapes() {
        for (const auto&[id, shape] : m_Shapes) {
            shape->Paint();
        }
    }

    /**
    * \brief Отрисовка фигуры на холсте
    * \param[in] aID идентификатор фигуры
    * \return CodeResults код ошибки
    */
    CodeResults PaintShape(const shapeid_t aID) {
        auto iter = m_Shapes.find(aID);
        if (iter == m_Shapes.end()) {
            return CodeResults::SomeError;
        }
        return iter->second->Paint();
    }

    /**
    * \brief Удаляет фигуру с холста
    * \param[in] aID идентификатор фигуры
    * \return CodeResults код ошибки
    */
    CodeResults EraseShape(const shapeid_t aID) {
        auto iter = m_Shapes.find(aID);
        if (iter == m_Shapes.end()) {
            return CodeResults::SomeError;
        }
        m_Shapes.erase(iter);
        return CodeResults::Succes;
    }
#pragma endregion

#pragma region ChangeStatePainterMethods
    /**
    * \brief Отчистить состояние маляра
    * \details уничтожит все фигуры, обнулит холст, сбросит генератор ID
    */
    void Clear() {
        m_Id.Clear();
        m_Shapes.clear();
        m_Canvas->Clear();
    }
#pragma endregion

#pragma region CanvasHandlers
    /**
    * \brief Изменеяет размер холста
    * \param[in] aX новая ширина холста
    * \param[in] aY новая высота холста
    * \return CodeResults код ошибки
    */
    CodeResults ResizeCanvas(const std::size_t aX, const std::size_t aY) {
        std::cout << "Painter: Resize Canvas\r\n";
        auto res = m_Canvas->Resize(aX, aY);
        if (res != CodeResults::Succes)
            return res;
        return CodeResults::Succes;
    }

    /**
    * \brief Замена фона холста
    * \param[in] aColor новый цвет ARGB
    * \return CodeResults код ошибки
    */
    CodeResults ChangeCanvasColor(const TColor aColor) {
        std::cout << "Painter: Resize Canvas\r\n";//Фигуры перерисовывать не надо
        auto res = m_Canvas->ChangeColor(aColor);
        if (res != CodeResults::Succes)
            return res;
        return CodeResults::Succes;
    }
    
    /**
    * \brief Замена холста
    * \param[in] aCanvas новый холст 
    * \details после изменения холста все фигуры получат новый холст и будут заново отрисованы
    * \return CodeResults код ошибки
    */
    CodeResults ChangeCanvas(std::unique_ptr<Canvas> aCanvas) {
        m_Canvas = std::move(aCanvas);
        for (auto&[id, shape] : m_Shapes) {
            shape->ChangeCanvas(m_Canvas);
        }
        PaintAllShapes();
        return CodeResults::Succes;
    }

    /**
    * \brief Получить размер текущего холста
    * \return std::pair<std::size_t, std::size_t>  ширина и высота холста
    */
    std::pair<std::size_t, std::size_t> GetCanvasSize() const{
        return m_Canvas->GetSize();
    }
#pragma endregion

private:
    Painter() = default;
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

