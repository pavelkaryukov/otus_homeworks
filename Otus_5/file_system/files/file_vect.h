#pragma once
#include "file_system/files/ifile.h"
/**
* \brief ����� Vect-file
* \details ������ �������������� ��� ����������, ������ ���� ������ �� ������ ��������(������������ ��� ������) �� � ������
*/
class FileVect final: public IFile {
public:
    FileVect() = default;
    
    /**
    * \brief ����������� �����
    * \param[in] aPath - ���� � �����
    * \return CodeResults ��� ������
    */
    explicit FileVect(const std::filesystem::path aPath) : IFile(aPath) {}

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
        std::cout << "FileVect::Save(); FileName: " << m_Path << std::endl;
        return CodeResults::Succes;
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
        const std::size_t testX = 1600, testY = 1200;//�������� �������, 
        const TColor testColor = { 89, 76, 25, 9 };
        return std::make_unique<Canvas>(testX, testY, testColor);
    }

    /**
    * \brief �������� ������ �� �����
    * \param[out] aPainter- �����, � ������� ����� ��������� ������
    * \return CodeResults ��� ������
    */
    CodeResults GetShapes(Painter& aPainter) override {
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Line>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Rectangle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        return {};
    }
};
