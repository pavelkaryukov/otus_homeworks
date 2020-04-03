#pragma once
#include "file_system/files/ifile.h"
///\brief Класс JPG-file
struct FileJPG : public IFile {
    FileJPG() = default;
    
    /**
    * \brief Конструктор файла
    * \param[in] aPath - путь к файлу
    * \return ErrorCode код ошибки
    */
    FileJPG(const std::filesystem::path aPath) : IFile(aPath) {}

    /**
    * \brief Открытие файла
    * \return ErrorCode код ошибки
    */
    ErrorCode Open() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Создание файла
    * \return ErrorCode код ошибки
    */
    ErrorCode Create() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Сохранение файла
    * \return ErrorCode код ошибки
    */
    ErrorCode Save() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Закрытие файла
    * \return ErrorCode код ошибки
    */
    ErrorCode Close() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Получить холст из файла
    * \return ErrorCode код ошибки
    */
    std::unique_ptr<Canvas> GetCanvas() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Получить фигуры из файла
    * \param[out] aPainter- Маляр, в который будут добавлены фигуры
    * \return ErrorCode код ошибки
    */
    ErrorCode GetShapes(Painter& aPainter) override {
        throw std::logic_error("The method or operation is not implemented.");
    }

};
