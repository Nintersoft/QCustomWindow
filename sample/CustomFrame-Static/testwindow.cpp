/*-------------------------------------------------
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
------------------------------------------------- */

#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    NMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    // Sets the custom Widgets on the parent Class
    // Otherwise, the window resizing feature will not work
    NMainWindow::setCustomWidgets(ui->centralWidget, ui->statusBar);

    clicks = 0;
    connect(ui->pushButton, &QPushButton::clicked, [this]{
        setWindowTitle("Number of clicks : " + QString::number(++clicks));
    });
}

TestWindow::~TestWindow()
{
    delete ui;
}
