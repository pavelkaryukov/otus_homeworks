#pragma once
#include <exception>
#include <stdexcept>
#include <cstdint>
#include <type_traits>
#include <memory>
#include "error_code/my_error_code.h"
#include "shape/utility/coord.h"
#include "shape/utility/color.h"
///\brief Интерфейс фигуры
struct IShape { 
    using thickens_t = std::uint8_t;

    IShape(
        const TCoord aCoordBegin,
        const TCoord aCoordEnd,
        const std::uint8_t aThickness,
        const TColor aColor
    ) :
        m_CoordBegin(aCoordBegin),
        m_CoordEnd  (aCoordEnd),
        m_Thickness (aThickness),
        m_Color     (aColor)
    {}

    //TODO::Возможно стоит переделать под SetState или типа того
    ErrorCode SetState( const TCoord aCoordBegin, const TCoord aCoordEnd, const std::uint8_t aThickness, const TColor aColor ) {
        m_CoordBegin = aCoordBegin; 
        m_CoordEnd   = aCoordEnd  ; 
        m_Thickness  = aThickness ; 
        m_Color      = aColor     ;
        return StateIsValid() ? ErrorCode::Succes : ErrorCode::Error1;
    }
    IShape() = default;
    /**
    * \brief функция создает копию фигуры
    * \return  std::unique_ptr<IShape>  указатель на интерфейс IShape
    */
    virtual std::unique_ptr<IShape> Clone(const TCoord aCoordBegin, const TCoord aCoordEnd) = 0;
    /**
    * \brief функция Отрисовывает фигуру на рабочей поверхности
    * \return  ErrorCode  Код возможной ошибки
    */
    virtual ErrorCode Paint() = 0;
    ///\brief деструктор
    virtual ~IShape() {}
    
    ///\brief Получить ширину линии
    thickens_t GetThickness() const {
        return m_Thickness;
    }
    ///\brief цвет ширину линии фигуры
    void ChangeThickness(const std::uint8_t aThickness) {
        m_Thickness = aThickness; //Оператор сравнения
    }
    ///\brief получить цвет фигуры
    TColor GetColor() const {
        return m_Color;
    }
    ///\brief изменить цвет фигуры
    void ChangeColor(TColor aColor) {
        m_Color = aColor;
    }
private:
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
//TODO::Не уверен, что правильно все продумал, но мне кажется логичным, сделать функцию, что возвращает ещё и код ошибки
template<class T>
std::pair<ErrorCode, std::unique_ptr<T>> CreateShapeOld
( 
    const TCoord       aCoordBegin, 
    const TCoord       aCoordEnd  , 
    const std::uint8_t aThickness , 
    const TColor       aColor
) 
{
    static_assert (std::is_base_of<IShape, T>::value);
    std::unique_ptr<T> shape = std::make_unique<T>();// (new T());
    IShape* ishape = shape.get();
    const auto res = ishape->SetState(aCoordBegin, aCoordEnd, aThickness, aColor);
    if (res == ErrorCode::Succes) {
        return  { ErrorCode::Succes, std::move(shape) };
    }

    return  { res, nullptr };
    //return  (res == ErrorCode::Succes) ? { ErrorCode::Succes, std::move(shape) } : { res, nullptr };
}
