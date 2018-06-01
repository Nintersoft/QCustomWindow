#-------------------------------------------------
#
# Project created by QtCreator 2018-05-29T00:56:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomFrameTestIn
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += ./nmainwindow

SOURCES += \
        main.cpp \
        nmainwindow/titlebar.cpp \
        nmainwindow/nmainwindow.cpp \
        testwindow.cpp

HEADERS += \
        nmainwindow/titlebar.h \
        nmainwindow/nmainwindow.h \
        testwindow.h

FORMS += \
        nmainwindow/titlebar.ui \
        nmainwindow/nmainwindow.ui \
        testwindow.ui
