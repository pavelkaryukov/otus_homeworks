#pragma once
///\brief Коды возвращаемых ошибок
enum class CodeResults {//Предполагается дальнейшее расширение
    Succes,
    CantPaintShapeOnCanvas,
    NoAccessToElement,
    CantResizeCanvas,
    SomeError
};