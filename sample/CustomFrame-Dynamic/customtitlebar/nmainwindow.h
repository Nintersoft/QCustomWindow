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

#ifndef NMAINWINDOW_H
#define NMAINWINDOW_H

#include <QtCore/qglobal.h>

#if defined(CUSTOMTITLEBAR_LIBRARY)
#  define CUSTOMTITLEBARSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CUSTOMTITLEBARSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <QPoint>
#include <QCloseEvent>
#include <QMainWindow>
#include <QMouseEvent>

#include "titlebar.h"

namespace Ui {
class NMainWindow;
}

class CUSTOMTITLEBARSHARED_EXPORT NMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NMainWindow(QWidget *parent = nullptr);
    ~NMainWindow();

    void setCustomWidgets(QWidget *newCentralWidget, QStatusBar *newStatusBar);
    void setNewCentralWidget(QWidget *newCentralWidget);
    void setCustomStatusBar(QStatusBar *newStatusBar);

    void setCloseButtonEnabled(bool enable);
    void setMaximizeButtonEnabled(bool enable);
    void setMinimizeButtonEnabled(bool enable);

    void setTitlebarStylesheet(const QString &styleSheet);
    QString titlebarStylesheet() const;

protected:
    void closeEvent(QCloseEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void undefMouseMoveEvent(QObject *object, QMouseEvent* event);
    bool eventFilter(QObject *watched, QEvent *event);
    
    enum LockMoveType{
        Left,
        Right,
        Top,
        Bottom,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        None
    };

private:
    Ui::NMainWindow *ui;
    const int RESIZE_LIMIT;

    QPoint posCursor;
    LockMoveType locked;
};

#endif // NMAINWINDOW_H
