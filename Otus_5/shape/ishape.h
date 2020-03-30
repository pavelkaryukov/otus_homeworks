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
    ///\brief положение начала объекта на экране
    TCoord CoordBegin;
    ///\brief положение конца объекта на экране
    TCoord CoordEnd;
    ///\brief толщина линии
    std::uint8_t Thickness;
    ///\brief цвет фигуры
    TColor Color;
    //TODO::Возможно стоит переделать под SetState или типа того
    ErrorCode SetState( const TCoord aCoordBegin, const TCoord aCoordEnd, const std::uint8_t aThickness, const TColor aColor ) {
        CoordBegin = aCoordBegin; 
        CoordEnd   = aCoordEnd  ; 
        Thickness  = aThickness ; 
        Color      = aColor     ;
        return StateIsValid() ? ErrorCode::Succes : ErrorCode::Error1;
    }
    IShape() = default;

    ///\brief цвет ширину линии фигуры
    void ChangeThickness(const std::uint8_t aThickness) 
    {
        Thickness = aThickness; //Оператор сравнения
    }
    ///\brief изменить цвет фигуры
    void ChangeColor(TColor aColor) {
        Color = aColor;
    }
    /**
    * \brief функция создает копию фигуры
    * \return  std::unique_ptr<IShape>  указатель на интерфейс IShape
    */
    virtual std::unique_ptr<IShape> Clone() = 0;
    /**
    * \brief функция Отрисовывает фигуру на рабочей поверхности
    * \return  ErrorCode  Код возможной ошибки
    */
    virtual ErrorCode Paint() = 0;
    ///\brief деструктор
    virtual ~IShape() {}
private:
    bool StateIsValid() {
        return true;
    }
};
///\brief Создает фигуру
//TODO::Не уверен, что правильно все продумал, но мне кажется логичным, сделать функцию, что возвращает ещё и код ошибки
template<class T>
std::pair<ErrorCode, std::unique_ptr<T>> CreateShape
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
