#pragma once
#include "file_system/all_files.h"
#include "work_space/canvas.h"
//Засунуть лямбду вызова select file from application
class FileManager final {
public:   
    /**
    * \brief импортирует класс художника из файла
    * \param[out] aPainter перенастраиваемый художник
    * \details Осуществляется замена холста и отрисованных фигур
    * \return  CodeResults  код ошибки
    */
    CodeResults Import(Painter& aPainter) {
        auto [res, filePtr] = SelectFile();
        if (res != CodeResults::Succes)
            return res;
        m_File = std::move(filePtr);
        auto resCode = aPainter.ChangeCanvas(m_File->GetCanvas());
        if (resCode != CodeResults::Succes)
            return resCode;
        resCode = m_File->GetShapes(aPainter);
        if (resCode != CodeResults::Succes)
            return resCode;
        return CodeResults::Succes;
    }
    
    /**
    * \brief экспорт состояние художника в файл
    * \param[in] aPainter объект класса художник
    * \return  CodeResults  код ошибки
    */
    CodeResults Export(const Painter& aPainter) {
        auto [res, filePtr] = SelectFile();
        if (res != CodeResults::Succes)
            return res;
        std::cout << "FileManager:: CodeResults Export(); FileName: " << filePtr->GetFileName() << std::endl;
        return CodeResults::Succes;
    }

    /**
    * \brief сохранение состояние художника в файл
    * \param[in] aPainter объект класса художник
    * \return  CodeResults  код ошибки
    */
    CodeResults Save(const Painter& aPainter) {
        if (m_File != nullptr)
            return m_File->Save();

        auto [error, ptr] = CreateFile("test_file.vect");

        if (error != CodeResults::Succes || ptr == nullptr) {
            return error;
        }
        m_File = std::move(ptr);
        m_File->Save();
        return CodeResults::Succes;
    }

private:
    std::unique_ptr<IFile> m_File;

    //Путь к файлу
    using OperationResult = std::pair<CodeResults, std::unique_ptr<IFile>>;

    OperationResult CreateFile(const std::filesystem::path aPath, const FileTypes aFType = FileTypes::VECT) {
        OperationResult  res = { CodeResults::Succes, std::unique_ptr<IFile>() };
        auto&[resCode, ptr] = res;

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
            resCode = CodeResults::SomeError;

        return res;
    }

    OperationResult SelectFile() {
        //Диалог выбора файла
        const std::filesystem::path filePath = "testfile.vect";
        OperationResult  res = { CodeResults::Succes, std::unique_ptr<IFile>(new FileVect(filePath)) };
        return res;
    }
};
