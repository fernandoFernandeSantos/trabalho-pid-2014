#-------------------------------------------------
#
# Project created by QtCreator 2014-07-21T20:14:48
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrabalhoPID
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    BitMapHeader.cpp \
    BMP.cpp \
    CollorPallet.cpp \
    Header.cpp \
    Pixel.cpp

HEADERS  += mainwindow.h \
    BitMapHeader.h \
    BMP.h \
    CollorPallet.h \
    Header.h \
    Matriz.h \
    Pixel.h \
    Vetor.h

FORMS    += mainwindow.ui

#OTHER_FILES +=
