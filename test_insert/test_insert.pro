QT -= gui
QT += sql

CONFIG += c++17 console
CONFIG -= app_bundle

include($$PWD/../tools/tools.pri)
INCLUDEPATH += $$PWD/../tools

SOURCES += \
        main.cpp
