#pragma once
#include "error_code/my_error_code.h"
#include "work_space/canvas.h"
#include "shape/ishape.h"
#include <filesystem> 
//Поддерживаемые файлы
enum class FileTypes {
    BMP,
    JPG,
    VECT,
    UNK
};
///\brief интерфейс файла
struct IFile {
    IFile() : m_Path("") {}

    /**
    * \brief Конструктор файла
    * \param[in] aPath - путь к файлу
    * \return ErrorCode код ошибки
    */
    IFile(const std::filesystem::path aPath) : m_Path(aPath) {}

    /**
    * \brief Открытие файла
    * \return ErrorCode код ошибки
    */
    virtual ErrorCode Open() = 0;

    /**
    * \brief Создание файла
    * \return ErrorCode код ошибки
    */
    virtual ErrorCode Create() = 0;

    /**
    * \brief Сохранение файла
    * \return ErrorCode код ошибки
    */
    virtual ErrorCode Save() = 0;

    /**
    * \brief Закрытие файла
    * \return ErrorCode код ошибки
    */
    virtual ErrorCode Close() = 0;
    
    /**
    * \brief Получить холст из файла
    * \return ErrorCode код ошибки
    */
    virtual std::unique_ptr<Canvas> GetCanvas() = 0;              // При экспорте файла - файловый мэнеджер получает канвас и набор фигур
    
    /**
    * \brief Получить фигуры из файла
    * \param[out] aPainter- Маляр, в который будут добавлены фигуры
    * \return ErrorCode код ошибки
    */
    virtual ErrorCode GetShapes(Painter& aPainter) = 0; // При экспорте файла - файловый мэнеджер получает канвас и набор фигур
    
    /**
    * \brief Получить холст из файла
    * \return ErrorCode код ошибки
    */
    std::filesystem::path GetFileName() const {
        return m_Path;
    }

    virtual ~IFile() {};
protected:
    std::filesystem::path m_Path;
};
