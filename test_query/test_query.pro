QT -= gui
QT += sql

CONFIG += c++17 console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../ $$PWD/../tools

SOURCES += \
        main.cpp

test_query.depends += tools
LIBS += -L../tools/lib -ltools
