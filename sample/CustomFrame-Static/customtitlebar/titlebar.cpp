/*-------------------------------------------------
#
# Project developed by Nintersoft team
# Developer: Mauro Mascarenhas de Araújo
# Contact: mauro.mascarenhas@nintersoft.com
# Licence: Mozilla Public Licence 2.0
# Date: 21 of December of 2019
#
# Licence notice
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
------------------------------------------------- */

#include "titlebar.h"
#include "ui_titlebar.h"

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
    setMainWindow(parent->parentWidget() ? parent->parentWidget() : parent);

    canMove = false;
}

TitleBar::~TitleBar()
{
    delete ui;
}

void TitleBar::setMainWindow(QWidget *mainWindow){
    this->parent = mainWindow;

    disconnect(ui->btClose, &QPushButton::clicked, this, &TitleBar::onCloseRequest);
    disconnect(ui->btMinimize, &QPushButton::clicked, this->parent, &QWidget::showMinimized);
    disconnect(ui->btMaximize, &QPushButton::clicked, this, &TitleBar::maximizeParent);

    disconnect(this->parent, &QWidget::windowTitleChanged, ui->lblFormTitle, &QLabel::setText);

    connect(ui->btClose, &QPushButton::clicked, this, &TitleBar::onCloseRequest);
    connect(ui->btMinimize, &QPushButton::clicked, this->parent, &QWidget::showMinimized);
    connect(ui->btMaximize, &QPushButton::clicked, this, &TitleBar::maximizeParent);

    connect(this->parent, &QWidget::windowTitleChanged, ui->lblFormTitle, &QLabel::setText);
}

void TitleBar::maximizeParent(){
    if (parent->isMaximized()) parent->showNormal();
    else parent->showMaximized();
}

void TitleBar::onCloseRequest(){
    emit closeRequest();
}

QWidget* TitleBar::mainWindow(){
    return this->parent;
}

void TitleBar::setCloseButtonEnabled(bool enable){
    ui->btClose->setEnabled(enable);
}

void TitleBar::setMaximizeButtonEnabled(bool enable){
    ui->btMaximize->setEnabled(enable);
}

void TitleBar::setMinimizeButtonEnabled(bool enable){
    ui->btMinimize->setEnabled(enable);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        canMove = !(event->x() < 5 || event->x() > (parent->width() - 5) || event->y() < 5);
        m_pCursor = event->globalPos() - parent->geometry().topLeft();
        event->accept();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (!canMove){
        event->accept();
        return;
    }
    if (event->buttons() & Qt::LeftButton){
        if (parent->isMaximized()){
            event->accept();
            return;
        }
        parent->move(event->globalPos() - m_pCursor);
        event->accept();
    }
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event){
    if (!ui->btMaximize->isEnabled()){
        event->accept();
        return;
    }
    if (event->button() == Qt::LeftButton) maximizeParent();
}

void TitleBar::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
