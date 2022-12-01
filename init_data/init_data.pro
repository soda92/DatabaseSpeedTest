QT -= gui
QT += sql

CONFIG += c++17 console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../ $$PWD/../tools

SOURCES += \
        main.cpp

init_data.depends += tools
LIBS += -L../tools/lib -ltools
