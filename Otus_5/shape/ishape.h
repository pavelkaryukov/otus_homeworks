#pragma once
#include <exception>
#include <stdexcept>
#include <cstdint>
#include <type_traits>
#include <memory>
#include "error_code/my_error_code.h"
#include "shape/utility/coord.h"
#include "shape/utility/color.h"
///\brief ��������� ������
struct IShape {                
    ///\brief ��������� ������ ������� �� ������
    TCoord CoordBegin;
    ///\brief ��������� ����� ������� �� ������
    TCoord CoordEnd;
    ///\brief ������� �����
    std::uint8_t Thickness;
    ///\brief ���� ������
    TColor Color;
    //TODO::�������� ����� ���������� ��� SetState ��� ���� ����
    ErrorCode SetState( const TCoord aCoordBegin, const TCoord aCoordEnd, const std::uint8_t aThickness, const TColor aColor ) {
        CoordBegin = aCoordBegin; 
        CoordEnd   = aCoordEnd  ; 
        Thickness  = aThickness ; 
        Color      = aColor     ;
        return StateIsValid() ? ErrorCode::Succes : ErrorCode::Error1;
    }
    IShape() = default;

    ///\brief ���� ������ ����� ������
    void ChangeThickness(const std::uint8_t aThickness) 
    {
        Thickness = aThickness; //�������� ���������
    }
    ///\brief �������� ���� ������
    void ChangeColor(TColor aColor) {
        Color = aColor;
    }
    /**
    * \brief ������� ������� ����� ������
    * \return  std::unique_ptr<IShape>  ��������� �� ��������� IShape
    */
    virtual std::unique_ptr<IShape> Clone() = 0;
    /**
    * \brief ������� ������������ ������ �� ������� �����������
    * \return  ErrorCode  ��� ��������� ������
    */
    virtual ErrorCode Paint() = 0;
    ///\brief ����������
    virtual ~IShape() {}
private:
    bool StateIsValid() {
        return true;
    }
};
///\brief ������� ������
//TODO::�� ������, ��� ��������� ��� ��������, �� ��� ������� ��������, ������� �������, ��� ���������� ��� � ��� ������
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
