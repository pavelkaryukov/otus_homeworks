#pragma once
#include <exception>
#include <cstdint>

///\brief Координата объекта на экране
struct TCoord 
{
    ///\brief Координата объекта на экране
    std::size_t X;
    ///\brief Координата объекта на экране
    std::size_t Y;
    const TCoord operator-(const TCoord& aRhs)
    {  
        X = (X >= aRhs.X) ? X - aRhs.X : 0;
        Y = (Y >= aRhs.Y) ? Y - aRhs.Y : 0;
    }
};
///\brief цвет объекта на экране
struct TColor {
    ///\brief прозрачность пикселя
    std::uint8_t Alpha;
    ///\brief красный цвет пикселя
    std::uint8_t Red;
    ///\brief зеленый цвет пикселя
    std::uint8_t Green;
    ///\brief синия цвет пикселя
    std::uint8_t Blue;
};
///\brief Ширина объекта
struct TThickness 
{    
    //TODO:: Возможно стоит убрать операторы
    TThickness operator=(const TThickness& aRhs) 
    {
        Value = aRhs.Value;
        if (Value == 0)
            Value = 1;
        return *this;
    }
    
    TThickness operator-(const std::size_t aDelta) 
    {
        Value = (aDelta < Value) ? Value - aDelta : 1;
    }
    
    TThickness operator+(const std::size_t aDelta) 
    {
        
        Value += aDelta;
        return *this;
    }

    bool operator==(const std::size_t aDelta) const
    {
        return Value == aDelta;
    }

    TThickness() = default;
    TThickness(const std::size_t aThick) 
    {
        Value = (aThick != 0) ? aThick : 1;
    }

    //ширина от нуля 
private:
    std::uint8_t Value : 4;//Ширина до 16
};

///\brief Интерфейс фигуры
struct IShape
{                
    ///\brief положение начала объекта на экране
    TCoord CoordBegin;
    ///\brief положение конца объекта на экране
    TCoord CoordEnd;
    ///\brief толщина линии
    TThickness Thickness;
    ///\brief цвет фигуры
    TColor Color;
    /**
    * \brief Перенос фигуры
    * \param[in] aNewBegin новая позиция начала
    */
    void Move(TCoord aNewBegin)
    {
        throw std::exception(" не реализованн метод (нет проверки на выход за пределы экрана)");
        // Move надо переделать, так что бы не было выхода за пределы экрана
    }
    /**
    * \brief Изменить размер фигуры
    * \param[in] aEndBegin новая позиция конца
    */
    void Resize(TCoord aEndBegin)
    {
        CoordEnd = aEndBegin;
    }
    ///\brief цвет ширину линии фигуры
    void ChangeThickness(std::size_t aThickness)
    {
        Thickness = TThickness(aThickness); //Оператор сравнения
    }
    ///\brief изменить цвет фигуры
    void ChangeColor(TColor aColor)
    {
        Color = aColor;
    }
    /**
    * \brief функция создает копию фигуры
    * \return  IShape*  указатель на интерфейс IShape
    */
    virtual IShape* Clone() = 0;
    ///\brief деструктор
    virtual ~IShape() = 0;
};
