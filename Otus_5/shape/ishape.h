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
///\brief ��������� ������
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
    * \brief ����� ��������� ������
    * \param[in] aCoordBegin - ���������� ������  ������
    * \param[in] aCoordEnd   - ���������� ������  ������
    * \param[in] aThickness  - ����� ������ ������
    * \param[in] aColor      - ����� ���� ������
    * \return ErrorCode ��� ������
    */
    ErrorCode SetState( const TCoord aCoordBegin, const TCoord aCoordEnd, const thickens_t aThickness, const TColor aColor ) {
        m_CoordBegin = aCoordBegin; 
        m_CoordEnd   = aCoordEnd  ; 
        m_Thickness  = aThickness ; 
        m_Color      = aColor     ;
        return StateIsValid() ? ErrorCode::Succes : ErrorCode::SomeError;
    }

    /**
    * \brief ������� ������� ����� ������
    * \param[in] aCoordBegin - ���������� ��������� ����� ������
    * \param[in] aCoordEnd   - ���������� ��������� ����� ������
    * \return  std::unique_ptr<IShape>  ��������� �� ��������� IShape
    */
    virtual std::unique_ptr<IShape> Clone(const TCoord aCoordBegin, const TCoord aCoordEnd) = 0;

    /**
    * \brief ������� ������������ ������ �� ������� �����������
    * \return  ErrorCode  ��� ��������� ������
    */
    virtual ErrorCode Paint() = 0;
    ///\brief ����������
    virtual ~IShape() {
        Erase();
    }

    ///\brief �������� ������ �����
    thickens_t GetThickness() const {
        return m_Thickness;
    }
    ///\brief ���� ������ ����� ������
    ErrorCode ChangeThickness(const std::uint8_t aThickness) {
        m_Thickness = aThickness; //�������� ���������
        return ErrorCode::Succes;
    }
    ///\brief �������� ���� ������
    TColor GetColor() const {
        return m_Color;
    }

    ///\brief �������� ���� ������
    ErrorCode ChangeColor(TColor aColor) {
        m_Color = aColor;
        return ErrorCode::Succes;
    }

    /**
    * \brief ������� ������ �� ������ �����
    * \param[in] aCanvas - ��������� �� ����� �����
    * \return  ErrorCode ��� ������
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
    * \brief ������� ������� ������ � ������� ����������� ()
    * \return  ErrorCode  ��� ��������� ������
    */
    void Erase() {
        std::cout << "Erase figure from Canvas: " << m_Canvas.get() << std::endl;
    }

    bool StateIsValid() {
        return true;
    }
    ///\brief ��������� ������ ������� �� ������
    TCoord m_CoordBegin;
    ///\brief ��������� ����� ������� �� ������
    TCoord m_CoordEnd;
    ///\brief ������� �����
    std::uint8_t m_Thickness;
    ///\brief ���� ������
    TColor m_Color;
};
///\brief ������� ������