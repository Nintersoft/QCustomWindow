/*-------------------------------------------------
#
# Project developed by Nintersoft team
# Developer: Mauro Mascarenhas de Araújo
# Contact: mauro.mascarenhas@nintersoft.com
# Licence: Mozilla Public Licence 2.0
# Date: 5 of September of 2021
#
# Licence notice
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
------------------------------------------------- */

#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>

#include "qcustomwindow.h"
#include "qcustomtitlebar.h"

namespace Ui {
class TestWindow;
}

class TestWindow : public QCustomWindow
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    Ui::TestWindow *ui;
    int clicks;
};

#endif // TESTWINDOW_H
