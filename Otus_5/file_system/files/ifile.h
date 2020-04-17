#pragma once
#include "code_results/my_code_results.h"
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
class IFile {
public:
    IFile() : m_Path("") {}

    /**
    * \brief Конструктор файла
    * \param[in] aPath - путь к файлу
    * \return CodeResults код ошибки
    */
    IFile(const std::filesystem::path aPath) : m_Path(aPath) {}

    /**
    * \brief Открытие файла
    * \return CodeResults код ошибки
    */
    virtual CodeResults Open() = 0;

    /**
    * \brief Создание файла
    * \return CodeResults код ошибки
    */
    virtual CodeResults Create() = 0;

    /**
    * \brief Сохранение файла
    * \return CodeResults код ошибки
    */
    virtual CodeResults Save() = 0;

    /**
    * \brief Закрытие файла
    * \return CodeResults код ошибки
    */
    virtual CodeResults Close() = 0;
    
    /**
    * \brief Получить холст из файла
    * \return CodeResults код ошибки
    */
    virtual std::unique_ptr<Canvas> GetCanvas() = 0;              // При экспорте файла - файловый мэнеджер получает канвас и набор фигур
    
    /**
    * \brief Получить фигуры из файла
    * \param[out] aPainter- Маляр, в который будут добавлены фигуры
    * \return CodeResults код ошибки
    */
    virtual CodeResults GetShapes(Painter& aPainter) = 0; // При экспорте файла - файловый мэнеджер получает канвас и набор фигур
    
    /**
    * \brief Получить холст из файла
    * \return CodeResults код ошибки
    */
    std::filesystem::path GetFileName() const {
        return m_Path;
    }

    virtual ~IFile() {};
protected:
    std::filesystem::path m_Path;
};
