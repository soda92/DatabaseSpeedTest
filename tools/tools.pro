TEMPLATE = lib
QT += core sql
TARGET = ../lib/tools

HEADERS += prepare_data.h \
    db_connection.h \
    random_data_generator.h \
    ../config.h \
    tools.h

SOURCES += prepare_data.cpp \
    db_connection.cpp \
    random_data_generator.cpp \

INCLUDEPATH += ../
