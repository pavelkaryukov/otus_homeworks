#pragma once
#include "error_code/my_error_code.h"
#include <filesystem> 

struct IFile {
    virtual ErrorCode Open  (const std::filesystem::path aPath) = 0;
    virtual ErrorCode Create(const std::filesystem::path aPath) = 0;
    virtual ErrorCode Save() = 0;
    virtual ErrorCode Write() = 0;
    virtual ErrorCode Close() = 0;
    virtual ~IFile() = 0;
};

struct FileJPG : public IFile {


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

};

struct FileBMP : public IFile {


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

};

struct FileUnk : public IFile {


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

};