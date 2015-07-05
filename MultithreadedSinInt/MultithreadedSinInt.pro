#-------------------------------------------------
#
# Project created by QtCreator 2015-07-04T17:06:56
#
#-------------------------------------------------

QT       -= core gui

TARGET = MultithreadedSinInt
TEMPLATE = lib
CONFIG += staticlib

CONFIG(debug, debug|release) {
    DESTDIR = ../Debug
}
CONFIG(release, debug|release) {
    DESTDIR = ../Release
}

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -static-libgcc

SOURCES += \
    ThreadPool.cpp \
    CalculateSin.cpp

HEADERS += \
    ThreadPool.h \
    CalculateSin.h
