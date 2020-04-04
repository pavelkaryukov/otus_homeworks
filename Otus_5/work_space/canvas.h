#pragma once
#include "shape/ishape.h"
#include "error_code/my_error_code.h"
#include <map>

/**
* \brief ����� �����
* \details ������� ���� ��� ��������� �����
*/
struct Canvas {
    Canvas() = default;
    
    /**
    * \brief ����������� ������
    * \param[in] aX  ������ ������
    * \param[in] aY  ������ ������
    * \param[in] aColor  ���� ���� ������ ARGB
    * \details ����� ��������� �������� ������ ��� ������ ����� ������ ����������
    * \return ErrorCode ��� ������
    */
    Canvas(const std::size_t aX, const std::size_t aY, const TColor aColor) : m_X(aX), m_Y(aY), m_Color(aColor) {}

    /**
    * \brief ��������� ������ ������
    * \param[in] aX ����� ������ ������
    * \param[in] aY ����� ������ ������
    * \return ErrorCode ��� ������
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
    * \brief ������ ����
    * \param[in] aColor ����� ���� ARGB
    * \details ����� ��������� ����� ������ ��� ������ ����� ������ ����������
    * \return ErrorCode ��� ������
    */
    ErrorCode ChangeColor(const TColor aColor) {
        m_Color = aColor;
        return ErrorCode::Succes;
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