#include <QApplication>
#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/Application.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Log::Init();
    Input::Init();

    ApplicationSpecification spec;
    spec.Name = "NIRS VIZ";
    spec.CommandLineArgs = { argc, argv };

    Application mainWindow = Application(spec);
    mainWindow.show();

    return app.exec();
}
