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

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOption>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

    void setMainWindow(QWidget *mainWindow);
    QWidget* mainWindow();

    void setCloseButtonEnabled(bool enable);
    void setMaximizeButtonEnabled(bool enable);
    void setMinimizeButtonEnabled(bool enable);

private:
    bool canMove;

    Ui::TitleBar *ui;
    QWidget *parent;
    QPoint m_pCursor;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

protected slots:
    void maximizeParent();
    void onCloseRequest();

signals:
    void closeRequest();
};

#endif // TITLEBAR_H
