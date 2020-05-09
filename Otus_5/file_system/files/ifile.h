#pragma once
#include "code_results/my_code_results.h"
#include "work_space/canvas.h"
#include "shape/ishape.h"
#include <filesystem> 
//�������������� �����
enum class FileTypes {
    BMP,
    JPG,
    VECT,
    UNK
};
///\brief ��������� �����
class IFile {
public:
    IFile() : m_Path("") {}

    /**
    * \brief ����������� �����
    * \param[in] aPath - ���� � �����
    * \return CodeResults ��� ������
    */
    IFile(const std::filesystem::path aPath) : m_Path(aPath) {}

    /**
    * \brief �������� �����
    * \return CodeResults ��� ������
    */
    virtual CodeResults Open() = 0;

    /**
    * \brief �������� �����
    * \return CodeResults ��� ������
    */
    virtual CodeResults Create() = 0;

    /**
    * \brief ���������� �����
    * \return CodeResults ��� ������
    */
    virtual CodeResults Save() = 0;

    /**
    * \brief �������� �����
    * \return CodeResults ��� ������
    */
    virtual CodeResults Close() = 0;
    
    /**
    * \brief �������� ����� �� �����
    * \return CodeResults ��� ������
    */
    virtual std::unique_ptr<Canvas> GetCanvas() = 0;              // ��� �������� ����� - �������� �������� �������� ������ � ����� �����
    
    /**
    * \brief �������� ������ �� �����
    * \param[out] aPainter- �����, � ������� ����� ��������� ������
    * \return CodeResults ��� ������
    */
    virtual CodeResults GetShapes(Painter& aPainter) = 0; // ��� �������� ����� - �������� �������� �������� ������ � ����� �����
    
    /**
    * \brief �������� ����� �� �����
    * \return CodeResults ��� ������
    */
    std::filesystem::path GetFileName() const {
        return m_Path;
    }

    virtual ~IFile() {};
protected:
    std::filesystem::path m_Path;
};
