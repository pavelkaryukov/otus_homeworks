#pragma once
#include "file_system/files/ifile.h"

//Формат который воспринимает только мой графический редактор
struct FileVect : public IFile {
    FileVect() = default;
    FileVect(const std::filesystem::path aPath) : IFile(aPath) {}

    ErrorCode Open(const std::filesystem::path aPath) override {
        throw std::logic_error("The method or operation is not implemented.");
    }


    ErrorCode Create(const std::filesystem::path aPath) override {
        throw std::logic_error("The method or operation is not implemented.");
    }


    ErrorCode Save() override {
        std::cout << "FileVect::Save(); FileName: " << m_Path << std::endl;
        return ErrorCode::Succes;
    }


    ErrorCode Write() override {
        throw std::logic_error("The method or operation is not implemented.");
    }


    ErrorCode Close() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    std::unique_ptr<Canvas> GetCanvas() override {
        const std::size_t testX = 1600, testY = 1200;//Тестовые размеры, 
        return std::make_unique<Canvas>(testX, testY);
    }


    ErrorCode GetShapes(Painter& aPainter) override {
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Line>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Rectangle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        return {};
    }

};
