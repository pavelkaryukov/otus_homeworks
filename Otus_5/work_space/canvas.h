#pragma once
#include "shape/ishape.h"
#include "error_code/my_error_code.h"
#include <map>

/**
* \brief класс ’олст
* \details рабоча€ зона дл€ отрисовки фигур
*/
struct Canvas {
    Canvas() = default;
    
    /**
    * \brief конструктор холста
    * \param[in] aX  ширина холста
    * \param[in] aY  высота холста
    * \param[in] aColor  ÷вет фона холста ARGB
    * \details после изменени€ размеров холста все фигуры будут заново отрисованы
    * \return ErrorCode код ошибки
    */
    Canvas(const std::size_t aX, const std::size_t aY, const TColor aColor) : m_X(aX), m_Y(aY), m_Color(aColor) {}

    /**
    * \brief »змене€ет размер холста
    * \param[in] aX нова€ ширина холста
    * \param[in] aY нова€ высота холста
    * \return ErrorCode код ошибки
    */
    ErrorCode Resize(const std::size_t aX, const std::size_t aY) {
        m_X = aX;
        m_Y = aY;
        return ErrorCode::Succes;
    }

    ErrorCode Clear() {
        return ErrorCode::Succes;
    }

    /**
    * \brief «амена фона
    * \param[in] aColor новый цвет ARGB
    * \details после изменени€ ÷вета холста все фигуры будут заново отрисованы
    * \return ErrorCode код ошибки
    */
    ErrorCode ChangeColor(const TColor aColor) {
        m_Color = aColor;
        return ErrorCode::Succes;
    }

    /**
    * \brief ѕолучить размер
    * \return std::pair<std::size_t, std::size_t>  ширина и высота холста
    */
    std::pair<std::size_t, std::size_t> GetSize() const {
        return { m_X, m_Y };
    }

private:
    std::size_t m_X = 0;
    std::size_t m_Y = 0;
    TColor      m_Color;
};