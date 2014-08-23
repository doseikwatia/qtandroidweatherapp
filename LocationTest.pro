TEMPLATE = app

QT += qml quick widgets positioning network xml

SOURCES += main.cpp \
    weatherservice.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    weatherservice.h
