#pragma once
#include "error_code/my_error_code.h"
#include "shape/utility/coord.h"
#include "shape/utility/color.h"
#include "work_space/canvas.h"
#include <exception>
#include <stdexcept>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <iostream>
#include <boost/format.hpp>
///\brief Интерфейс фигуры
struct IShape { 
    using thickens_t = std::uint8_t;

    IShape(
        std::shared_ptr<Canvas> aCanvas,
        const TCoord aCoordBegin,
        const TCoord aCoordEnd,
        const std::uint8_t aThickness,
        const TColor aColor
    ) :
        m_Canvas(aCanvas),
        m_CoordBegin(aCoordBegin),
        m_CoordEnd  (aCoordEnd),
        m_Thickness (aThickness),
        m_Color     (aColor)
    {}

    /**
    * \brief смена состояния фигуры
    * \param[in] aCoordBegin - координаты нового  фигуры
    * \param[in] aCoordEnd   - координаты нового  фигуры
    * \param[in] aThickness  - новая ширина фигуры
    * \param[in] aColor      - новый цвет фигуры
    * \return ErrorCode код ошибки
    */
    ErrorCode SetState( const TCoord aCoordBegin, const TCoord aCoordEnd, const thickens_t aThickness, const TColor aColor ) {
        m_CoordBegin = aCoordBegin; 
        m_CoordEnd   = aCoordEnd  ; 
        m_Thickness  = aThickness ; 
        m_Color      = aColor     ;
        return StateIsValid() ? ErrorCode::Succes : ErrorCode::SomeError;
    }

    /**
    * \brief функция создает копию фигуры
    * \param[in] aCoordBegin - координаты положения копии фигуры
    * \param[in] aCoordEnd   - координаты положения копии фигуры
    * \return  std::unique_ptr<IShape>  указатель на интерфейс IShape
    */
    virtual std::unique_ptr<IShape> Clone(const TCoord aCoordBegin, const TCoord aCoordEnd) = 0;

    /**
    * \brief функция Отрисовывает фигуру на рабочей поверхности
    * \return  ErrorCode  Код возможной ошибки
    */
    virtual ErrorCode Paint() = 0;
    ///\brief деструктор
    virtual ~IShape() {
        Erase();
    }

    ///\brief Получить ширину линии
    thickens_t GetThickness() const {
        return m_Thickness;
    }
    ///\brief цвет ширину линии фигуры
    ErrorCode ChangeThickness(const std::uint8_t aThickness) {
        m_Thickness = aThickness; //Оператор сравнения
        return ErrorCode::Succes;
    }
    ///\brief получить цвет фигуры
    TColor GetColor() const {
        return m_Color;
    }

    ///\brief изменить цвет фигуры
    ErrorCode ChangeColor(TColor aColor) {
        m_Color = aColor;
        return ErrorCode::Succes;
    }

    /**
    * \brief перенос фигуры на другой холст
    * \param[in] aCanvas - указатель на новый холст
    * \return  ErrorCode код ошибки
    */
    ErrorCode ChangeCanvas(std::shared_ptr<Canvas> aCanvas) {
        m_Canvas = aCanvas;
        return ErrorCode::Succes;
    }
protected:
    std::shared_ptr<Canvas> m_Canvas;
private:
    IShape() = default;
    /**
    * \brief функция Стирает фигуру с рабочей поверхности ()
    * \return  ErrorCode  Код возможной ошибки
    */
    void Erase() {
        std::cout << "Erase figure from Canvas: " << m_Canvas.get() << std::endl;
    }

    bool StateIsValid() {
        return true;
    }
    ///\brief положение начала объекта на экране
    TCoord m_CoordBegin;
    ///\brief положение конца объекта на экране
    TCoord m_CoordEnd;
    ///\brief толщина линии
    std::uint8_t m_Thickness;
    ///\brief цвет фигуры
    TColor m_Color;
};
///\brief Создает фигуру