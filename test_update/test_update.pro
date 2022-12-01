QT -= gui
QT += sql

CONFIG += c++17 console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../ $$PWD/../tools

SOURCES += \
        test_update.cpp

test_update.depends += tools
LIBS += -L../tools/lib -ltools
