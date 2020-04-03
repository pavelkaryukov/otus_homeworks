#pragma once
#include "file_system/all_files.h"
#include "work_space/canvas.h"
//Засунуть лямбду вызова select file from application
struct FileManager {
    
    /**
    * \brief импортирует класс художника из файла
    * \param[out] aPainter перенастраиваемый художник
    * \details Осуществляется замена холста и отрисованных фигур
    * \return  ErrorCode  код ошибки
    */
    ErrorCode Import(Painter& aPainter) {
        auto [res, filePtr] = SelectFile();
        if (res != ErrorCode::Succes)
            return res;
        m_File = std::move(filePtr);
        auto errorCode = aPainter.ChangeCanvas(m_File->GetCanvas());
        if (errorCode != ErrorCode::Succes)
            return errorCode;

        errorCode = m_File->GetShapes(aPainter);
        if (errorCode != ErrorCode::Succes)
            return errorCode;
        return ErrorCode::Succes;
    }
    
    /**
    * \brief экспорт состояние художника в файл
    * \param[in] aPainter объект класса художник
    * \return  ErrorCode  код ошибки
    */
    ErrorCode Export(const Painter& aPainter) {
        auto [res, filePtr] = SelectFile();
        if (res != ErrorCode::Succes)
            return res;
        std::cout << "FileManager:: ErrorCode Export(); FileName: " << filePtr->GetFileName() << std::endl;
        return ErrorCode::Succes;
    }

    /**
    * \brief сохранение состояние художника в файл
    * \param[in] aPainter объект класса художник
    * \return  ErrorCode  код ошибки
    */
    ErrorCode Save(const Painter& aPainter) {
        if (m_File != nullptr)
            return m_File->Save();

        auto [error, ptr] = CreateFile("test_file.vect");

        if (error != ErrorCode::Succes || ptr == nullptr) {
            return error;
        }
        m_File = std::move(ptr);
        m_File->Save();
        return ErrorCode::Succes;
    }

private:
    std::unique_ptr<IFile> m_File;

    //Путь к файлу
    using OperationResult = std::pair<ErrorCode, std::unique_ptr<IFile>>;

    OperationResult CreateFile(const std::filesystem::path aPath, const FileTypes aFType = FileTypes::VECT) {
        OperationResult  res = { ErrorCode::Succes, std::unique_ptr<IFile>() };
        auto&[errorCode, ptr] = res;

         switch (aFType) {
             case FileTypes::BMP:
                 ptr = std::make_unique<FileBMP>(aPath);
                 break;
             case FileTypes::JPG:
                 ptr = std::make_unique<FileJPG>(aPath);
                 break;
             case FileTypes::VECT:
                 ptr = std::make_unique<FileVect>(aPath);
                 break;
         }

        if (ptr == nullptr) 
            errorCode = ErrorCode::SomeError;

        return res;
    }

    OperationResult SelectFile() {
        //Диалог выбора файла
        const std::filesystem::path filePath = "testfile.vect";
        OperationResult  res = { ErrorCode::Succes, std::unique_ptr<IFile>(new FileVect(filePath)) };
        return res;
    }
};
