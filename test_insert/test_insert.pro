QT -= gui
QT += sql

CONFIG += c++17 console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../ $$PWD/../tools

SOURCES += \
        test_insert.cpp

test_insert.depends += tools
LIBS += -L../tools/lib -ltools
