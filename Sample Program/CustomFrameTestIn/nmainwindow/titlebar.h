/*-------------------------------------------------
#
# Project developed by Nintersoft team
# Developer: Mauro Mascarenhas de Araújo
# Contact: mauro.mascarenhas@nintersoft.com
# License: Nintersoft Open Source Code Licence
# Date: 31 of May of 2018
#
------------------------------------------------- */

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

    void setMainWindow(QWidget *mainWindow);
    QWidget* mainWindow();

    void setCloseButtonEnabled(bool enable);
    void setMaximizeButtonEnabled(bool enable);
    void setMinimizeButtonEnabled(bool enable);

private:
    Ui::TitleBar *ui;
    QWidget *parent;
    QPoint m_pCursor;
    bool canMove;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

protected slots:
    void maximizeParent();
};

#endif // TITLEBAR_H
