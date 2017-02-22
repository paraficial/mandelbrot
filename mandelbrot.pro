#-------------------------------------------------
#
# Project created by QtCreator 2017-02-21T22:26:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mandelbrot
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mandelbrot.cpp

HEADERS  += widget.h \
    mandelbrot.h

FORMS    += widget.ui
