#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "weatherservice.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
//    engine.addImageProvider("Photo",ImageProvider);
    qmlRegisterType<WeatherService>("WeatherService",1,0,"WeatherService");
    qmlRegisterType<WeatherInfo>("WeatherService",1,0,"WeatherInfo");
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
