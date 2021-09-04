/*-------------------------------------------------
#
# Project developed by Nintersoft team
# Developer: Mauro Mascarenhas de Araújo
# Contact: mauro.mascarenhas@nintersoft.com
# Licence: Mozilla Public Licence 2.0
# Date: 3 of September of 2021
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
    QCustomWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this->mainWindow());

    clicks = 0;
    connect(ui->pushButton, &QPushButton::clicked, [this]{
        setWindowTitle("Number of clicks : " + QString::number(++clicks));
    });
    this->setMinimumSize(500, 400);
}

TestWindow::~TestWindow()
{
    delete ui;
}
