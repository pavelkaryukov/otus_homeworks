#pragma once
#include "file_system/files/ifile.h"

struct FileBMP : public IFile {
    FileBMP() = default;
    FileBMP(const std::filesystem::path aPath) : IFile(aPath) {}

    ErrorCode Open(const std::filesystem::path aPath) override {
        throw std::logic_error("The method or operation is not implemented.");
    }


    ErrorCode Create(const std::filesystem::path aPath) override {
        throw std::logic_error("The method or operation is not implemented.");
    }


    ErrorCode Save() override {
        throw std::logic_error("The method or operation is not implemented.");
    }


    ErrorCode Write() override {
        throw std::logic_error("The method or operation is not implemented.");
    }


    ErrorCode Close() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    std::unique_ptr<Canvas> GetCanvas() override {
        throw std::logic_error("The method or operation is not implemented.");
    }


    ErrorCode GetShapes(Painter& aPainter) override {
        throw std::logic_error("The method or operation is not implemented.");
    }

};

