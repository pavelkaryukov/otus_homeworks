#pragma once
#include "shape/ishape.h"
#include "code_results/my_code_results.h"
#include <map>

/**
* \brief класс Холст
* \details рабочая зона для отрисовки фигур
*/
class Canvas final {
public:
    Canvas() = default;
    
    /**
    * \brief конструктор холста
    * \param[in] aX  ширина холста
    * \param[in] aY  высота холста
    * \param[in] aColor  Цвет фона холста ARGB
    * \details после изменения размеров холста все фигуры будут заново отрисованы
    * \return CodeResults код ошибки
    */
    Canvas(const std::size_t aX, const std::size_t aY, const TColor aColor) : m_X(aX), m_Y(aY), m_Color(aColor) {}

    /**
    * \brief Изменеяет размер холста
    * \param[in] aX новая ширина холста
    * \param[in] aY новая высота холста
    * \return CodeResults код ошибки
    */
    CodeResults Resize(const std::size_t aX, const std::size_t aY) {
        m_X = aX;
        m_Y = aY;
        return CodeResults::Succes;
    }

    CodeResults Clear() {
        return CodeResults::Succes;
    }

    /**
    * \brief Замена фона
    * \param[in] aColor новый цвет ARGB
    * \details после изменения Цвета холста все фигуры будут заново отрисованы
    * \return CodeResults код ошибки
    */
    CodeResults ChangeColor(const TColor aColor) {
        m_Color = aColor;
        return CodeResults::Succes;
    }

    /**
    * \brief Получить размер
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