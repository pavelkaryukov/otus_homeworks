#pragma once
#include "file_system/files/ifile.h"
/**
* \brief Класс Vect-file
* \details формат поддерживаемый мои редактором, внутри себя хранит не только картинку(используемую для холста) но и фигуры
*/
class FileVect final: public IFile {
public:
    FileVect() = default;
    
    /**
    * \brief Конструктор файла
    * \param[in] aPath - путь к файлу
    * \return CodeResults код ошибки
    */
    explicit FileVect(const std::filesystem::path aPath) : IFile(aPath) {}

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
        std::cout << "FileVect::Save(); FileName: " << m_Path << std::endl;
        return CodeResults::Succes;
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
        const std::size_t testX = 1600, testY = 1200;//Тестовые размеры, 
        const TColor testColor = { 89, 76, 25, 9 };
        return std::make_unique<Canvas>(testX, testY, testColor);
    }

    /**
    * \brief Получить фигуры из файла
    * \param[out] aPainter- Маляр, в который будут добавлены фигуры
    * \return CodeResults код ошибки
    */
    CodeResults GetShapes(Painter& aPainter) override {
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Line>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Rectangle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        aPainter.AddShape<Circle>({ 0, 9 }, { 10, 78 }, 6, { 89, 76, 22, 35 });
        return {};
    }
};
