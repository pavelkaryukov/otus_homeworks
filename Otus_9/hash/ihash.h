#pragma once
#include <string> 
/**
* \brief  интерфейс классов расчета хэш функций
*/
class IHash {
public:
    /**
    * \brief сделать расчет хэш функции для буффера
    * \param[in] aData - указатель на начало буфера
    * \param[in] aLen - длина буффера в байтах
    */    
    virtual void ProcessBuffer(const void* aData, const std::size_t aLen) = 0;
    
    /**
    * \brief  Получить рассчитанную раньше хэш функцию
    * \details возвращает результат последнего или общего (в зависимости от реализации класса наследника) расчета хэш суммы
    * \return std::string - хэш сумма представляется ввиде строки
    */
    virtual const std::string Result() = 0; // std::string удобней всего, так как для него реализованы операции сравнения 
};