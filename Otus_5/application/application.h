#pragma once
#include "work_space/painter.h"
#include "code_results/my_code_results.h"
#include "shape/circle.h"
#include "shape/rectangle.h"
#include "shape/line.h"
#include "file_system/file_manager.h"
#include <optional>
/*! \mainpage Otus_5 (graphic_editor)
 *
 * \r\n   Макет классов простейшего векторного редактора
 *
 */
 /*! Application class */
 /// \brief Класс векторный редактор (предполагается что гуи будет использовать его методы)
 /// \details содержит в себе файловый мэнеджер (class FileManager) и класс художник(ClassPainter)
class Application final{
public:
#pragma region Constructros
    ///\brief конструктор по умолчанию - размер холста будет 800x600
    Application() = default;

    /**
        * \brief конструктор
        * \param[in] aX Ширина холста
        * \param[in] aY Высота холста
        * \param[in] TColor Цвет фона холста
        * \param[in] aThickness Толщина линий, рисуемых фигур
        * \return  объект класса Application
        */
    Application(
        const std::size_t              aX,
        const std::size_t              aY,
        const TColor                   aColor,
        const IShape::thickens_t       aThickness) : m_Color(aColor), m_Thickness(aThickness) {
        m_Painter = Painter(Canvas{ aX, aY, TColor() });
    }
#pragma endregion

#pragma region ShapeAddingMethods  
    /**
    * \brief метод добавляет окружность на холст
    * \param[in] aBegin координата начала фигуры
    * \param[in] aEnd координата конца фигуры
    * \param[in] aThickness Толщина линий, рисуемых фигур
    * \param[in] TColor Цвет фона холста
    * \return  CodeResults  код ошибки
    */
    CodeResults AddCircle(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        std::cout << boost::format("Class Application:: method AddCircle\r\n");
        return m_Painter.AddShape<Circle>(aBegin, aEnd, aThck, aColor);
    }

    /**
    * \brief метод добавляет линию на холст
    * \param[in] aBegin координата начала фигуры
    * \param[in] aEnd координата конца фигуры
    * \param[in] aThickness Толщина линий, рисуемых фигур
    * \param[in] TColor Цвет фона холста
    * \return  CodeResults  код ошибки
    */
    CodeResults AddLine(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        std::cout << boost::format("Class Application:: method AddLine\r\n");
        return m_Painter.AddShape<Line>(aBegin, aEnd, aThck, aColor);
    }

    /**
    * \brief метод добавляет прямоугольник на холст
    * \param[in] aBegin координата начала фигуры
    * \param[in] aEnd координата конца фигуры
    * \param[in] aThickness Толщина линий, рисуемых фигур
    * \param[in] TColor Цвет фона холста
    * \return  CodeResults  код ошибки
    */
    CodeResults AddRectangle(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        std::cout << boost::format("Class Application:: method AddRectangle\r\n");
        return AddRectangle(aBegin, aEnd, aThck, aColor);
    }

    /**
    * \brief метод добавляет окружность на холст
    * \param[in] aBegin координата начала фигуры
    * \param[in] aEnd координата конца фигуры
    * \details Толщина линий и цвет будут выданы классом Application
    * \return  CodeResults  код ошибки
    */
    CodeResults AddCircle(const TCoord aBegin, const TCoord aEnd) {
        return AddCircle(aBegin, aEnd, m_Thickness, m_Color);
    }

    /**
    * \brief метод добавляет линию на холст
    * \param[in] aBegin координата начала фигуры
    * \param[in] aEnd координата конца фигуры
    * \details Толщина линий и цвет будут выданы классом Application
    * \return  CodeResults  код ошибки
    */
    CodeResults AddLine(const TCoord aBegin, const TCoord aEnd) {
        return AddLine(aBegin, aEnd, m_Thickness, m_Color);
    }

    /**
    * \brief метод добавляет прямоугольник на холст
    * \param[in] aBegin координата начала фигуры
    * \param[in] aEnd координата конца фигуры
    * \details Толщина линий и цвет будут выданы классом Application
    * \return  CodeResults  код ошибки
    */
    CodeResults AddRectangle(const TCoord aBegin, const TCoord aEnd) {
        return m_Painter.AddShape<Rectangle>(aBegin, aEnd, m_Thickness, m_Color);
    }
#pragma endregion

#pragma region ChangeStateAppMethods

    /**
    * \brief метод задает толщину рисуемых на холсте фигур
    * \param[in] aThickness толщина от 0 до 255
    */
    void SetThickness(const IShape::thickens_t aThickness) {
        std::cout << boost::format("Class Application:: method SetThickness\r\n");
        m_Thickness = aThickness;
    }

    /**
    * \brief метод задает цвет рисуемых на холсте фигур
    * \param[in] aColor цвет и интенсивность (ARGB)
    */
    void SetColor(const TColor aColor) {
        std::cout << boost::format("Class Application:: method SetColor\r\n");
        m_Color = aColor;
    }
#pragma endregion

#pragma  region ShapeHandlers

    /**
    * \brief метод возвращает ID выделенной фигуры
    * \param[in] aX положение мышки на холсте - ось абсцисс
    * \param[in] aY положение мышки на холсте - ось ординат
    * \details положение мышки передаст GUI
    * \return опциональное значение которого ID выделенной фигуры
    */
    std::optional<Painter::shapeid_t> SelectShape(const std::size_t aX, const std::size_t aY) {
        //Ткнул мышкой в экра - получил id фигуры  
        throw std::logic_error("Method SelectShape not implemented");
    }

    /**
    * \brief Метод удаляет фигуру с холста
    * \param[in] aID айдишник удаляемой фигуры
    * \details предполагается использование вкупе с SelectShape
    * \return CodeResults код ошибки
    */
    CodeResults DeleteShape(const std::size_t aID) {
        return m_Painter.EraseShape(aID);
    }
#pragma endregion

#pragma region CanvasHandlers

    /**
    * \brief Метод заменяет холст
    * \details предполагается вызов диалога выбора холста и его замена
    * \return CodeResults код ошибки
    */
    CodeResults ChangeCanvas() {
        //Диалог Смены канваса
        //Вызов ChangeCanvasColor
        return CodeResults::Succes;
    }

    /**
    * \brief Метод изменяет размер холста
    * \details все фигуры сохранятся на холсте
    * \return CodeResults код ошибки
    */
    CodeResults ResizeCanvas(const std::size_t aX, const std::size_t aY) {
        return m_Painter.ResizeCanvas(aX, aY);
    }

    /**
    * \brief Метод изменяет цвет холста
    * \details все фигуры сохранятся на холсте
    * \return CodeResults код ошибки
    */
    CodeResults ChangeCanvasColor(const TColor aColor) {
        return m_Painter.ChangeCanvasColor(aColor);
    }

    /**
    * \brief Метод возвращает текущий размер холста
    * \return std::pair<std::size_t, std::size_t> ширина + высота холста
    */
    std::pair<std::size_t, std::size_t> GetCanvasSize() const {
        return m_Painter.GetCanvasSize();
    }
#pragma endregion

#pragma region FileSystemMethods

    /**
    * \brief Импорт состояния редактора из файла
    * \details Импорт холст и фигур (фигуры будут получены только если файл *.vect) из файла
    * \return CodeResults код ошибки
    */
    CodeResults Import() {
        m_Painter.Clear();
        auto resCode = m_FileManager.Import(m_Painter);
        auto res = m_Painter.GetCanvasSize();
        return CodeResults::Succes;
    }

    /**
    * \brief Экспорт состояния редактора в файл
    * \details Экспорт холста и фигур (фигуры будут экспортированны только если файл *.vect) в файла
    * \return CodeResults код ошибки
    */
    CodeResults Export() {
        return m_FileManager.Export(m_Painter);
    }

    /**
    * \brief Сохранение текущего состояния редактора
    * \return CodeResults код ошибки
    */
    CodeResults Save() {
        return m_FileManager.Save(m_Painter);
    }
#pragma endregion

private:
    TColor                   m_Color;
    IShape::thickens_t       m_Thickness;
    Painter                  m_Painter = Painter(Canvas{ 800, 600, {} });
    FileManager              m_FileManager;
};