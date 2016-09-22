#-------------------------------------------------
#
# Project created by QtCreator 2016-09-22T11:39:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Recognizer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    grammar.cpp \
    grammarstringlist.cpp

HEADERS  += widget.h \
    grammar.h \
    grammarstringlist.h

FORMS    += widget.ui
