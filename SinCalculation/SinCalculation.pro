#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T00:41:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SinCalculation
TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR = ../Debug
}
CONFIG(release, debug|release) {
    DESTDIR = ../Release
}

QMAKE_CXX += -static
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    CalculationThread.cpp

HEADERS  += MainWindow.h \
    CalculationThread.h

FORMS    += MainWindow.ui

CONFIG(debug, debug|release) {
    LIBS += ../Debug/libMultithreadedSinInt.a
}
CONFIG(release, debug|release) {
    LIBS += ../Release/libMultithreadedSinInt.a
}
