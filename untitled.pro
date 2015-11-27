#-------------------------------------------------
#
# Project created by QtCreator 2015-10-03T14:30:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameBoard.cpp \
    player.cpp \
    computerPlayer.cpp \
    humanPlayer.cpp

HEADERS  += mainwindow.h \
    gameBoard.h \
    player.h \
    computerPlayer.h \
    humanPlayer.h \
    util/utilities.h

FORMS    += mainwindow.ui
