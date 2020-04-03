#pragma once
///\brief Коды возвращаемых ошибок
enum class ErrorCode {//Предполагается дальнейшее расширение
    Succes,
    CantPaintShapeOnCanvas,
    NoAccessToElement,
    CantResizeCanvas,
    SomeError
};