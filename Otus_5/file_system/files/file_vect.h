#pragma once
#include "file_system/files/ifile.h"
/**
* \brief Класс Vect-file
* \details формат поддерживаемый мои редактором, внутри себя хранит не только картинку(используемую для холста) но и фигуры
*/
struct FileVect : public IFile {
    FileVect() = default;
    
    /**
    * \brief Конструктор файла
    * \param[in] aPath - путь к файлу
    * \return ErrorCode код ошибки
    */
    FileVect(const std::filesystem::path aPath) : IFile(aPath) {}

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
        std::cout << "FileVect::Save(); FileName: " << m_Path << std::endl;
        return ErrorCode::Succes;
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
        const std::size_t testX = 1600, testY = 1200;//Тестовые размеры, 
        const TColor testColor = { 89, 76, 25, 9 };
        return std::make_unique<Canvas>(testX, testY, testColor);
    }

    /**
    * \brief Получить фигуры из файла
    * \param[out] aPainter- Маляр, в который будут добавлены фигуры
    * \return ErrorCode код ошибки
    */
    ErrorCode GetShapes(Painter& aPainter) override {
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Line>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Rectangle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        return {};
    }
};
