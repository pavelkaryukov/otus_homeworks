#pragma once
#include "work_space/painter.h"
#include "code_results/my_code_results.h"
#include "shape/circle.h"
#include "shape/rectangle.h"
#include "shape/line.h"
#include "file_system/file_manager.h"
#include <optional>
/*! \mainpage Otus_5 (graphic_editor)
 *
 * \r\n   ����� ������� ����������� ���������� ���������
 *
 */
 /*! Application class */
 /// \brief ����� ��������� �������� (�������������� ��� ��� ����� ������������ ��� ������)
 /// \details �������� � ���� �������� �������� (class FileManager) � ����� ��������(ClassPainter)
class Application final{
public:
#pragma region Constructros
    ///\brief ����������� �� ��������� - ������ ������ ����� 800x600
    Application() = default;

    /**
        * \brief �����������
        * \param[in] aX ������ ������
        * \param[in] aY ������ ������
        * \param[in] TColor ���� ���� ������
        * \param[in] aThickness ������� �����, �������� �����
        * \return  ������ ������ Application
        */
    Application(
        const std::size_t              aX,
        const std::size_t              aY,
        const TColor                   aColor,
        const IShape::thickens_t       aThickness) : m_Color(aColor), m_Thickness(aThickness) {
        m_Painter = Painter(Canvas{ aX, aY, TColor() });
    }
#pragma endregion

#pragma region ShapeAddingMethods  
    /**
    * \brief ����� ��������� ���������� �� �����
    * \param[in] aBegin ���������� ������ ������
    * \param[in] aEnd ���������� ����� ������
    * \param[in] aThickness ������� �����, �������� �����
    * \param[in] TColor ���� ���� ������
    * \return  CodeResults  ��� ������
    */
    CodeResults AddCircle(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        std::cout << boost::format("Class Application:: method AddCircle\r\n");
        return m_Painter.AddShape<Circle>(aBegin, aEnd, aThck, aColor);
    }

    /**
    * \brief ����� ��������� ����� �� �����
    * \param[in] aBegin ���������� ������ ������
    * \param[in] aEnd ���������� ����� ������
    * \param[in] aThickness ������� �����, �������� �����
    * \param[in] TColor ���� ���� ������
    * \return  CodeResults  ��� ������
    */
    CodeResults AddLine(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        std::cout << boost::format("Class Application:: method AddLine\r\n");
        return m_Painter.AddShape<Line>(aBegin, aEnd, aThck, aColor);
    }

    /**
    * \brief ����� ��������� ������������� �� �����
    * \param[in] aBegin ���������� ������ ������
    * \param[in] aEnd ���������� ����� ������
    * \param[in] aThickness ������� �����, �������� �����
    * \param[in] TColor ���� ���� ������
    * \return  CodeResults  ��� ������
    */
    CodeResults AddRectangle(const TCoord aBegin, const TCoord aEnd, const IShape::thickens_t aThck, const TColor aColor) {
        std::cout << boost::format("Class Application:: method AddRectangle\r\n");
        return AddRectangle(aBegin, aEnd, aThck, aColor);
    }

    /**
    * \brief ����� ��������� ���������� �� �����
    * \param[in] aBegin ���������� ������ ������
    * \param[in] aEnd ���������� ����� ������
    * \details ������� ����� � ���� ����� ������ ������� Application
    * \return  CodeResults  ��� ������
    */
    CodeResults AddCircle(const TCoord aBegin, const TCoord aEnd) {
        return AddCircle(aBegin, aEnd, m_Thickness, m_Color);
    }

    /**
    * \brief ����� ��������� ����� �� �����
    * \param[in] aBegin ���������� ������ ������
    * \param[in] aEnd ���������� ����� ������
    * \details ������� ����� � ���� ����� ������ ������� Application
    * \return  CodeResults  ��� ������
    */
    CodeResults AddLine(const TCoord aBegin, const TCoord aEnd) {
        return AddLine(aBegin, aEnd, m_Thickness, m_Color);
    }

    /**
    * \brief ����� ��������� ������������� �� �����
    * \param[in] aBegin ���������� ������ ������
    * \param[in] aEnd ���������� ����� ������
    * \details ������� ����� � ���� ����� ������ ������� Application
    * \return  CodeResults  ��� ������
    */
    CodeResults AddRectangle(const TCoord aBegin, const TCoord aEnd) {
        return m_Painter.AddShape<Rectangle>(aBegin, aEnd, m_Thickness, m_Color);
    }
#pragma endregion

#pragma region ChangeStateAppMethods

    /**
    * \brief ����� ������ ������� �������� �� ������ �����
    * \param[in] aThickness ������� �� 0 �� 255
    */
    void SetThickness(const IShape::thickens_t aThickness) {
        std::cout << boost::format("Class Application:: method SetThickness\r\n");
        m_Thickness = aThickness;
    }

    /**
    * \brief ����� ������ ���� �������� �� ������ �����
    * \param[in] aColor ���� � ������������� (ARGB)
    */
    void SetColor(const TColor aColor) {
        std::cout << boost::format("Class Application:: method SetColor\r\n");
        m_Color = aColor;
    }
#pragma endregion

#pragma  region ShapeHandlers

    /**
    * \brief ����� ���������� ID ���������� ������
    * \param[in] aX ��������� ����� �� ������ - ��� �������
    * \param[in] aY ��������� ����� �� ������ - ��� �������
    * \details ��������� ����� �������� GUI
    * \return ������������ �������� �������� ID ���������� ������
    */
    std::optional<Painter::shapeid_t> SelectShape(const std::size_t aX, const std::size_t aY) {
        //����� ������ � ���� - ������� id ������  
        throw std::logic_error("Method SelectShape not implemented");
    }

    /**
    * \brief ����� ������� ������ � ������
    * \param[in] aID �������� ��������� ������
    * \details �������������� ������������� ����� � SelectShape
    * \return CodeResults ��� ������
    */
    CodeResults DeleteShape(const std::size_t aID) {
        return m_Painter.EraseShape(aID);
    }
#pragma endregion

#pragma region CanvasHandlers

    /**
    * \brief ����� �������� �����
    * \details �������������� ����� ������� ������ ������ � ��� ������
    * \return CodeResults ��� ������
    */
    CodeResults ChangeCanvas() {
        //������ ����� �������
        //����� ChangeCanvasColor
        return CodeResults::Succes;
    }

    /**
    * \brief ����� �������� ������ ������
    * \details ��� ������ ���������� �� ������
    * \return CodeResults ��� ������
    */
    CodeResults ResizeCanvas(const std::size_t aX, const std::size_t aY) {
        return m_Painter.ResizeCanvas(aX, aY);
    }

    /**
    * \brief ����� �������� ���� ������
    * \details ��� ������ ���������� �� ������
    * \return CodeResults ��� ������
    */
    CodeResults ChangeCanvasColor(const TColor aColor) {
        return m_Painter.ChangeCanvasColor(aColor);
    }

    /**
    * \brief ����� ���������� ������� ������ ������
    * \return std::pair<std::size_t, std::size_t> ������ + ������ ������
    */
    std::pair<std::size_t, std::size_t> GetCanvasSize() const {
        return m_Painter.GetCanvasSize();
    }
#pragma endregion

#pragma region FileSystemMethods

    /**
    * \brief ������ ��������� ��������� �� �����
    * \details ������ ����� � ����� (������ ����� �������� ������ ���� ���� *.vect) �� �����
    * \return CodeResults ��� ������
    */
    CodeResults Import() {
        m_Painter.Clear();
        auto resCode = m_FileManager.Import(m_Painter);
        auto res = m_Painter.GetCanvasSize();
        return CodeResults::Succes;
    }

    /**
    * \brief ������� ��������� ��������� � ����
    * \details ������� ������ � ����� (������ ����� ��������������� ������ ���� ���� *.vect) � �����
    * \return CodeResults ��� ������
    */
    CodeResults Export() {
        return m_FileManager.Export(m_Painter);
    }

    /**
    * \brief ���������� �������� ��������� ���������
    * \return CodeResults ��� ������
    */
    CodeResults Save() {
        return m_FileManager.Save(m_Painter);
    }
#pragma endregion

private:
    TColor                   m_Color;
    IShape::thickens_t       m_Thickness;
    Painter                  m_Painter = Painter(Canvas{ 800, 600, {} });
    FileManager              m_FileManager;
};