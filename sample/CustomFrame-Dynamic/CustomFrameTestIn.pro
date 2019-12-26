#-------------------------------------------------
#
# Project developed by Nintersoft team
# Developer: Mauro Mascarenhas de Araújo
# Contact: mauro.mascarenhas@nintersoft.com
# Licence: Mozilla Public Licence 2.0
# Date: 25 of December of 2019
#
# Licence notice
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
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

INCLUDEPATH += $$PWD/customtitlebar
DEPENDPATH += $$PWD/customtitlebar

SOURCES += \
        main.cpp \
        testwindow.cpp

HEADERS += testwindow.h

FORMS += testwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/customtitlebar/ -lCustomTitlebar
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/customtitlebar/ -lCustomTitlebar
