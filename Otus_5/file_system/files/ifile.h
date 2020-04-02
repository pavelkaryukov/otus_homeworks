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
//Maybe destroe default constructors?
struct IFile {
    IFile() : m_Path("") {}
    IFile(const std::filesystem::path aPath) : m_Path(aPath) {}

    virtual ErrorCode Open(const std::filesystem::path aPath) = 0;
    virtual ErrorCode Create(const std::filesystem::path aPath) = 0;
    virtual ErrorCode Save() = 0;
    virtual ErrorCode Write() = 0;
    virtual ErrorCode Close() = 0;
    virtual std::unique_ptr<Canvas> GetCanvas() = 0;              // При экспорте файла - файловый мэнеджер получает канвас и набор фигур
    virtual ErrorCode GetShapes(Painter& aPainter) = 0; // При экспорте файла - файловый мэнеджер получает канвас и набор фигур
    std::filesystem::path GetFileName() const {
        return m_Path;
    }

    //std::vector<IShape> Transform
    virtual ~IFile() {};
protected:
    std::filesystem::path m_Path;
};
