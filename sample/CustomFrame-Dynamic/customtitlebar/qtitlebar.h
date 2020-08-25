/*-------------------------------------------------
#
# Project developed by Nintersoft team
# Developer: Mauro Mascarenhas de Araújo
# Contact: mauro.mascarenhas@nintersoft.com
# Licence: Mozilla Public Licence 2.0
# Date: 24 of August of 2020
#
# Licence notice
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
------------------------------------------------- */

#ifndef QTITLEBAR_H
#define QTITLEBAR_H

#include <QtCore/qglobal.h>

#if defined(QCUSTOMTITLEBAR_LIBRARY)
#  define QCUSTOMTITLEBARSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QCUSTOMTITLEBARSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <QSize>
#include <QEvent>
#include <QLabel>
#include <QPoint>
#include <QWidget>
#include <QPainter>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPushButton>
#include <QStyleOption>

#include <exception>

namespace QCustomAttrs {
    enum WindowButton {
        Minimize = 0x01,
        Maximize = 0x02,
        Close    = 0x04,
        All      = Minimize | Maximize | Close
    };

    Q_DECLARE_FLAGS(WindowButtons, WindowButton)
    Q_DECLARE_OPERATORS_FOR_FLAGS(WindowButtons)
}

class QCUSTOMTITLEBARSHARED_EXPORT QTitleBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QCustomAttrs::WindowButtons windowButtons READ windowButtons WRITE setWindowButtons)
    Q_CLASSINFO("custom_obj_type", "QTitleBar")
public:
    explicit QTitleBar(QMainWindow *parent = nullptr);

    void setWindowButtons(QCustomAttrs::WindowButtons btns);
    inline QCustomAttrs::WindowButtons windowButtons() const { return this->m_frameButtons; }

    void setWindowButtonEnabled(QCustomAttrs::WindowButton btn, bool enabled = true);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    bool canMove;
    bool maximizing;

    QPoint m_pCursor;
    const QSize FRAME_BUTTON_SIZE;

    QWidget *m_parentWindow;

    QCustomAttrs::WindowButtons m_frameButtons;

    QLabel lbl_windowTitle;
    QHBoxLayout m_layout;
    QPushButton btn_minimize;
    QPushButton btn_maximize;
    QPushButton btn_close;

signals:
    void requestClose();
    void requestMaximize();
    void requestMinimize();
};

#endif // QTITLEBAR_H
