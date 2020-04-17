#pragma once
#include "file_system/files/ifile.h"
///\brief ����� BMP-file
class FileBMP final : public IFile {
public:
    FileBMP() = default;
    /**
    * \brief ����������� BMP �����
    * \param[in] aPath - ���� � �����
    * \return CodeResults ��� ������
    */
    FileBMP(const std::filesystem::path aPath) : IFile(aPath) {}
    
    /**
    * \brief �������� �����
    * \return CodeResults ��� ������
    */
    CodeResults Open() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief �������� �����
    * \return CodeResults ��� ������
    */
    CodeResults Create() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief ���������� �����
    * \return CodeResults ��� ������
    */
    CodeResults Save() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief �������� �����
    * \return CodeResults ��� ������
    */
    CodeResults Close() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief �������� ����� �� �����
    * \return CodeResults ��� ������
    */
    std::unique_ptr<Canvas> GetCanvas() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief �������� ������ �� �����
    * \param[out] aPainter- �����, � ������� ����� ��������� ������
    * \return CodeResults ��� ������
    */
    CodeResults GetShapes(Painter& aPainter) override {
        throw std::logic_error("The method or operation is not implemented.");
    }
};

