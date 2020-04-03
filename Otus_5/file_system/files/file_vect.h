#pragma once
#include "file_system/files/ifile.h"
/**
* \brief ����� Vect-file
* \details ������ �������������� ��� ����������, ������ ���� ������ �� ������ ��������(������������ ��� ������) �� � ������
*/
struct FileVect : public IFile {
    FileVect() = default;
    
    /**
    * \brief ����������� �����
    * \param[in] aPath - ���� � �����
    * \return ErrorCode ��� ������
    */
    FileVect(const std::filesystem::path aPath) : IFile(aPath) {}

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
        std::cout << "FileVect::Save(); FileName: " << m_Path << std::endl;
        return ErrorCode::Succes;
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
        const std::size_t testX = 1600, testY = 1200;//�������� �������, 
        const TColor testColor = { 89, 76, 25, 9 };
        return std::make_unique<Canvas>(testX, testY, testColor);
    }

    /**
    * \brief �������� ������ �� �����
    * \param[out] aPainter- �����, � ������� ����� ��������� ������
    * \return ErrorCode ��� ������
    */
    ErrorCode GetShapes(Painter& aPainter) override {
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Line>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Rectangle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        return {};
    }
};
