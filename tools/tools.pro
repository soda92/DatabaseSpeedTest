TEMPLATE = lib
QT += core sql
TARGET = ../lib/tools

HEADERS += $$PWD/prepare_data.h \
    $$PWD/db_connection.h \
    $$PWD/random_data_generator.h \
    $$PWD/../config.h \
    $$PWD/tools.h

SOURCES += $$PWD/prepare_data.cpp \
    $$PWD/db_connection.cpp \
    $$PWD/random_data_generator.cpp \

INCLUDEPATH += $$PWD/../
