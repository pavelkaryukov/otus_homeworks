#pragma once
#include "error_code/my_error_code.h"
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
struct IFile {
    IFile() : m_Path("") {}

    /**
    * \brief ����������� �����
    * \param[in] aPath - ���� � �����
    * \return ErrorCode ��� ������
    */
    IFile(const std::filesystem::path aPath) : m_Path(aPath) {}

    /**
    * \brief �������� �����
    * \return ErrorCode ��� ������
    */
    virtual ErrorCode Open() = 0;

    /**
    * \brief �������� �����
    * \return ErrorCode ��� ������
    */
    virtual ErrorCode Create() = 0;

    /**
    * \brief ���������� �����
    * \return ErrorCode ��� ������
    */
    virtual ErrorCode Save() = 0;

    /**
    * \brief �������� �����
    * \return ErrorCode ��� ������
    */
    virtual ErrorCode Close() = 0;
    
    /**
    * \brief �������� ����� �� �����
    * \return ErrorCode ��� ������
    */
    virtual std::unique_ptr<Canvas> GetCanvas() = 0;              // ��� �������� ����� - �������� �������� �������� ������ � ����� �����
    
    /**
    * \brief �������� ������ �� �����
    * \param[out] aPainter- �����, � ������� ����� ��������� ������
    * \return ErrorCode ��� ������
    */
    virtual ErrorCode GetShapes(Painter& aPainter) = 0; // ��� �������� ����� - �������� �������� �������� ������ � ����� �����
    
    /**
    * \brief �������� ����� �� �����
    * \return ErrorCode ��� ������
    */
    std::filesystem::path GetFileName() const {
        return m_Path;
    }

    virtual ~IFile() {};
protected:
    std::filesystem::path m_Path;
};
