#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Pass the engine to the controller, which will handle loading the QML
    Controller controller(&engine);
    return app.exec();
}

