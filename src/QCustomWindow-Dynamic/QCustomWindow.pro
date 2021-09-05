# -------------------------------------------------
#
# Project developed by Nintersoft team
# Developer: Mauro Mascarenhas de Araújo
# Contact: mauro.mascarenhas@nintersoft.com
# Licence: Mozilla Public Licence 2.0
# Date: 04 of September of 2021
#
# Licence notice
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
# -------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCustomWindow
TEMPLATE = lib

win32 {
    VERSION = 3.0.1

    QMAKE_TARGET_COMPANY = Nintersoft
    QMAKE_TARGET_PRODUCT = QCustomWindow
    QMAKE_TARGET_DESCRIPTION = QCustomWindow
    QMAKE_TARGET_COPYRIGHT = Copyright (c) 2021 - Nintersoft

    CONFIG += skip_target_version_ext
}
else {
    VERSION = 3.0.1
    CONFIG += unversioned_libname
}

DEFINES += QCUSTOMWINDOW_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        qcustomtitlebar.cpp \
        qcustomwindow.cpp

HEADERS += \
         qcustomtitlebar.h \
         qcustomwindow.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
