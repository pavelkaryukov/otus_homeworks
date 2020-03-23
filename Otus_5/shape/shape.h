#pragma once
#include <exception>
#include <cstdint>

///\brief ���������� ������� �� ������
struct TCoord 
{
    ///\brief ���������� ������� �� ������
    std::size_t X;
    ///\brief ���������� ������� �� ������
    std::size_t Y;
    const TCoord operator-(const TCoord& aRhs)
    {  
        X = (X >= aRhs.X) ? X - aRhs.X : 0;
        Y = (Y >= aRhs.Y) ? Y - aRhs.Y : 0;
    }
};
///\brief ���� ������� �� ������
struct TColor {
    ///\brief ������������ �������
    std::uint8_t Alpha;
    ///\brief ������� ���� �������
    std::uint8_t Red;
    ///\brief ������� ���� �������
    std::uint8_t Green;
    ///\brief ����� ���� �������
    std::uint8_t Blue;
};
///\brief ������ �������
struct TThickness 
{    
    //TODO:: �������� ����� ������ ���������
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

    //������ �� ���� 
private:
    std::uint8_t Value : 4;//������ �� 16
};

///\brief ��������� ������
struct IShape
{                
    ///\brief ��������� ������ ������� �� ������
    TCoord CoordBegin;
    ///\brief ��������� ����� ������� �� ������
    TCoord CoordEnd;
    ///\brief ������� �����
    TThickness Thickness;
    ///\brief ���� ������
    TColor Color;
    /**
    * \brief ������� ������
    * \param[in] aNewBegin ����� ������� ������
    */
    void Move(TCoord aNewBegin)
    {
        throw std::exception(" �� ����������� ����� (��� �������� �� ����� �� ������� ������)");
        // Move ���� ����������, ��� ��� �� �� ���� ������ �� ������� ������
    }
    /**
    * \brief �������� ������ ������
    * \param[in] aEndBegin ����� ������� �����
    */
    void Resize(TCoord aEndBegin)
    {
        CoordEnd = aEndBegin;
    }
    ///\brief ���� ������ ����� ������
    void ChangeThickness(std::size_t aThickness)
    {
        Thickness = TThickness(aThickness); //�������� ���������
    }
    ///\brief �������� ���� ������
    void ChangeColor(TColor aColor)
    {
        Color = aColor;
    }
    /**
    * \brief ������� ������� ����� ������
    * \return  IShape*  ��������� �� ��������� IShape
    */
    virtual IShape* Clone() = 0;
    ///\brief ����������
    virtual ~IShape() = 0;
};
