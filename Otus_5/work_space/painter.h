#pragma once
#include "shape/ishape.h"
#include "work_space/canvas.h" 
#include <map>

/**
* \brief ����� Painter (�����)
* \details ����� �����, ������ � ���� ��� ������ � ������������ �� �� ������
*/
class Painter final {
public:
    using shapeid_t = std::size_t;
#pragma region Constructors

    /**
    * \brief ����������� ������ Painter
    * \param[in] aCanvas rvalue Canvas - ����
    * \details ������� ������ ������ �����
    * \return  ������ ������ Painter
    */
    Painter(Canvas&& aCanvas) {
        m_Canvas = std::make_shared<Canvas>(std::move(aCanvas));
    }
#pragma endregion

#pragma region ShapeHandlers
    /**
    * \brief ��������� ������ � ������������ �� ������
    * \param[in] aCoordBegin ���������� ������ ������
    * \param[in] aCoordEnd ���������� ����� ������
    * \param[in] aThickness ������ ����� ������
    * \param[in] aColor ���� ������ - ARGB
    * \details ��������� ������  � m_Shapes � ������������ �� ������
    * \return CodeResults ��� ������
    */
    template<class T>
    CodeResults AddShape(
        const TCoord       aCoordBegin,
        const TCoord       aCoordEnd,
        const std::uint8_t aThickness,
        const TColor       aColor
    ) {
        static_assert(std::is_base_of<IShape, T>::value);
        auto[iter, res] = m_Shapes.insert({ m_Id.Generate(), std::make_unique<T>(m_Canvas, aCoordBegin, aCoordEnd, aThickness, aColor) });
        if (!res) {
            return CodeResults::SomeError;
        }
        iter->second->Paint();
        return CodeResults::Succes;
    }

    /**
    * \brief ������������ ��� ������ �� ������
    */
    void PaintAllShapes() {
        for (const auto&[id, shape] : m_Shapes) {
            shape->Paint();
        }
    }

    /**
    * \brief ��������� ������ �� ������
    * \param[in] aID ������������� ������
    * \return CodeResults ��� ������
    */
    CodeResults PaintShape(const shapeid_t aID) {
        auto iter = m_Shapes.find(aID);
        if (iter == m_Shapes.end()) {
            return CodeResults::SomeError;
        }
        return iter->second->Paint();
    }

    /**
    * \brief ������� ������ � ������
    * \param[in] aID ������������� ������
    * \return CodeResults ��� ������
    */
    CodeResults EraseShape(const shapeid_t aID) {
        auto iter = m_Shapes.find(aID);
        if (iter == m_Shapes.end()) {
            return CodeResults::SomeError;
        }
        m_Shapes.erase(iter);
        return CodeResults::Succes;
    }
#pragma endregion

#pragma region ChangeStatePainterMethods
    /**
    * \brief ��������� ��������� ������
    * \details ��������� ��� ������, ������� �����, ������� ��������� ID
    */
    void Clear() {
        m_Id.Clear();
        m_Shapes.clear();
        m_Canvas->Clear();
    }
#pragma endregion

#pragma region CanvasHandlers
    /**
    * \brief ��������� ������ ������
    * \param[in] aX ����� ������ ������
    * \param[in] aY ����� ������ ������
    * \return CodeResults ��� ������
    */
    CodeResults ResizeCanvas(const std::size_t aX, const std::size_t aY) {
        std::cout << "Painter: Resize Canvas\r\n";
        auto res = m_Canvas->Resize(aX, aY);
        if (res != CodeResults::Succes)
            return res;
        return CodeResults::Succes;
    }

    /**
    * \brief ������ ���� ������
    * \param[in] aColor ����� ���� ARGB
    * \return CodeResults ��� ������
    */
    CodeResults ChangeCanvasColor(const TColor aColor) {
        std::cout << "Painter: Resize Canvas\r\n";//������ �������������� �� ����
        auto res = m_Canvas->ChangeColor(aColor);
        if (res != CodeResults::Succes)
            return res;
        return CodeResults::Succes;
    }
    
    /**
    * \brief ������ ������
    * \param[in] aCanvas ����� ����� 
    * \details ����� ��������� ������ ��� ������ ������� ����� ����� � ����� ������ ����������
    * \return CodeResults ��� ������
    */
    CodeResults ChangeCanvas(std::unique_ptr<Canvas> aCanvas) {
        m_Canvas = std::move(aCanvas);
        for (auto&[id, shape] : m_Shapes) {
            shape->ChangeCanvas(m_Canvas);
        }
        PaintAllShapes();
        return CodeResults::Succes;
    }

    /**
    * \brief �������� ������ �������� ������
    * \return std::pair<std::size_t, std::size_t>  ������ � ������ ������
    */
    std::pair<std::size_t, std::size_t> GetCanvasSize() const{
        return m_Canvas->GetSize();
    }
#pragma endregion

private:
    Painter() = default;
    std::map<std::size_t, std::unique_ptr<IShape>> m_Shapes;
    std::shared_ptr<Canvas>                        m_Canvas;

#pragma region GeneratorID
    struct IdGenerator {
        shapeid_t Generate() {
            return m_ShapeCounter++;
        }

        void Clear() {
            m_ShapeCounter = 0;
        }

        IdGenerator() = default;
    private:
        shapeid_t m_ShapeCounter = 0;
    };

    IdGenerator m_Id;
#pragma endregion
};

