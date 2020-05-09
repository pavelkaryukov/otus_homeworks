#pragma once
#include "shape/ishape.h"
#include "code_results/my_code_results.h"
#include <map>

/**
* \brief ����� �����
* \details ������� ���� ��� ��������� �����
*/
class Canvas final {
public:
    Canvas() = default;
    
    /**
    * \brief ����������� ������
    * \param[in] aX  ������ ������
    * \param[in] aY  ������ ������
    * \param[in] aColor  ���� ���� ������ ARGB
    * \details ����� ��������� �������� ������ ��� ������ ����� ������ ����������
    * \return CodeResults ��� ������
    */
    Canvas(const std::size_t aX, const std::size_t aY, const TColor aColor) : m_X(aX), m_Y(aY), m_Color(aColor) {}

    /**
    * \brief ��������� ������ ������
    * \param[in] aX ����� ������ ������
    * \param[in] aY ����� ������ ������
    * \return CodeResults ��� ������
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
    * \brief ������ ����
    * \param[in] aColor ����� ���� ARGB
    * \details ����� ��������� ����� ������ ��� ������ ����� ������ ����������
    * \return CodeResults ��� ������
    */
    CodeResults ChangeColor(const TColor aColor) {
        m_Color = aColor;
        return CodeResults::Succes;
    }

    /**
    * \brief �������� ������
    * \return std::pair<std::size_t, std::size_t>  ������ � ������ ������
    */
    std::pair<std::size_t, std::size_t> GetSize() const {
        return { m_X, m_Y };
    }

private:
    std::size_t m_X = 0;
    std::size_t m_Y = 0;
    TColor      m_Color;
};