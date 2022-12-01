QT -= gui
QT += sql

CONFIG += c++17 console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../ $$PWD/../tools

SOURCES += \
        test_query.cpp

test_query.depends += tools
LIBS += -L../tools/lib -ltools
