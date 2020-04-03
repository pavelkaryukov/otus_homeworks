#pragma once
#include "file_system/files/ifile.h"
///\brief ����� BMP-file
struct FileBMP : public IFile {
    FileBMP() = default;
    /**
    * \brief ����������� BMP �����
    * \param[in] aPath - ���� � �����
    * \return ErrorCode ��� ������
    */
    FileBMP(const std::filesystem::path aPath) : IFile(aPath) {}
    
    /**
    * \brief �������� �����
    * \return ErrorCode ��� ������
    */
    ErrorCode Open() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief �������� �����
    * \return ErrorCode ��� ������
    */
    ErrorCode Create() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief ���������� �����
    * \return ErrorCode ��� ������
    */
    ErrorCode Save() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief �������� �����
    * \return ErrorCode ��� ������
    */
    ErrorCode Close() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief �������� ����� �� �����
    * \return ErrorCode ��� ������
    */
    std::unique_ptr<Canvas> GetCanvas() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief �������� ������ �� �����
    * \param[out] aPainter- �����, � ������� ����� ��������� ������
    * \return ErrorCode ��� ������
    */
    ErrorCode GetShapes(Painter& aPainter) override {
        throw std::logic_error("The method or operation is not implemented.");
    }
};

