#pragma once
#include "file_system/files/ifile.h"
///\brief Класс BMP-file
class FileBMP final : public IFile {
public:
    FileBMP() = default;
    /**
    * \brief Конструктор BMP файла
    * \param[in] aPath - путь к файлу
    * \return CodeResults код ошибки
    */
    FileBMP(const std::filesystem::path aPath) : IFile(aPath) {}
    
    /**
    * \brief Открытие файла
    * \return CodeResults код ошибки
    */
    CodeResults Open() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Создание файла
    * \return CodeResults код ошибки
    */
    CodeResults Create() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Сохранение файла
    * \return CodeResults код ошибки
    */
    CodeResults Save() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Закрытие файла
    * \return CodeResults код ошибки
    */
    CodeResults Close() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Получить холст из файла
    * \return CodeResults код ошибки
    */
    std::unique_ptr<Canvas> GetCanvas() override {
        throw std::logic_error("The method or operation is not implemented.");
    }

    /**
    * \brief Получить фигуры из файла
    * \param[out] aPainter- Маляр, в который будут добавлены фигуры
    * \return CodeResults код ошибки
    */
    CodeResults GetShapes(Painter& aPainter) override {
        throw std::logic_error("The method or operation is not implemented.");
    }
};

