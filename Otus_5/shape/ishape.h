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

    //TODO::�������� ����� ���������� ��� SetState ��� ���� ����
    ErrorCode SetState( const TCoord aCoordBegin, const TCoord aCoordEnd, const std::uint8_t aThickness, const TColor aColor ) {
        m_CoordBegin = aCoordBegin; 
        m_CoordEnd   = aCoordEnd  ; 
        m_Thickness  = aThickness ; 
        m_Color      = aColor     ;
        return StateIsValid() ? ErrorCode::Succes : ErrorCode::SomeError;
    }
    /**
    * \brief ������� ������� ����� ������
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
    void ChangeThickness(const std::uint8_t aThickness) {
        m_Thickness = aThickness; //�������� ���������
    }
    ///\brief �������� ���� ������
    TColor GetColor() const {
        return m_Color;
    }
    ///\brief �������� ���� ������
    void ChangeColor(TColor aColor) {
        m_Color = aColor;
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