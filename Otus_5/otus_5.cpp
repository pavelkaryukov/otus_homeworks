#include "application/application.h"

void TestApplication() {
    Application app;
    app.SetColor(TColor(87, 128, 22, 88));
    app.SetThickness(2);
    app.AddCircle({ 0 , 66  }, { 88, 90 });
    app.AddCircle({ 33, 500 }, { 98, 756});
    app.AddLine  ({ 65, 36  }, { 80, 96 });
    app.SetColor(TColor(85, 66, 1, 82));
    app.SetThickness(15);
    app.AddRectangle({ 0 , 66  }, { 88, 90 });// его должен убить
    app.AddRectangle({ 33, 500 }, { 98, 756 });
    app.AddLine     ({ 65, 36  }, { 80, 96 });
    app.DeleteShape(3);
    app.ResizeCanvas(1024, 768);
    app.Export();
    app.Save();
    app.Import();
}

int main() {
    TestApplication();
}