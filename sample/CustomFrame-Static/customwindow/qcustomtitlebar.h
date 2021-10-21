/*-------------------------------------------------
#
# Project developed by Nintersoft team
# Developer: Mauro Mascarenhas de Araújo
# Contact: mauro.mascarenhas@nintersoft.com
# Licence: Mozilla Public Licence 2.0
# Date: 31 of October of 2021
#
# Licence notice
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
------------------------------------------------- */

#ifndef QCUSTOMTITLEBAR_H
#define QCUSTOMTITLEBAR_H

#include <QIcon>
#include <QSize>
#include <QEvent>
#include <QLabel>
#include <QPoint>
#include <QPointF>
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QtGlobal>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPushButton>
#include <QStyleOption>

#ifndef EV_GLOBAL_MACRO
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        #define EV_GLOBAL_X(event) event->globalX()
        #define EV_GLOBAL_Y(event) event->globalY()
        #define EV_GLOBAL_POS(event) event->globalPos()
    #else
        #define EV_GLOBAL_X(event) event->globalPosition().toPoint().x()
        #define EV_GLOBAL_Y(event) event->globalPosition().toPoint().y()
        #define EV_GLOBAL_POS(event) event->globalPosition().toPoint()
    #endif
    #define EV_GLOBAL_MACRO
#endif

namespace QCustomAttrs {
    enum WindowButton {
        Minimize = 0x01,
        Maximize = 0x02,
        Close    = 0x04
    };

    Q_DECLARE_FLAGS(WindowButtons, WindowButton)
    Q_DECLARE_OPERATORS_FOR_FLAGS(WindowButtons)
}

class QCustomTitleBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QCustomAttrs::WindowButtons windowButtons READ windowButtons WRITE setWindowButtons)
    Q_CLASSINFO("custom_obj_type", "QCustomTitleBar")
public:
    explicit QCustomTitleBar(QWidget *parent = nullptr);

    void setWindowButtons(QCustomAttrs::WindowButtons btns);
    inline QCustomAttrs::WindowButtons windowButtons() const { return this->mFrameButtons; }

    void setWindowButtonText(QCustomAttrs::WindowButton btn, const QString &text = "");
    void setWindowButtonEnabled(QCustomAttrs::WindowButton btn, bool enabled = true);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QPoint mPCursor;
    const QSize FRAME_BUTTON_SIZE;

    QCustomAttrs::WindowButtons mFrameButtons;

    QLabel lblWindowIcon;
    QLabel lblWindowTitle;
    QHBoxLayout mLayout;
    QPushButton btnMinimize;
    QPushButton btnMaximize;
    QPushButton btnClose;

signals:
    void closeRequest();
    void maximizeRequest();
    void minimizeRequest();

    void stopWindowMoveRequest();
    void startWindowMoveRequest(const QPoint &start);
    void changeWindowPositionRequest(const QPoint &to);
};

#endif // QCUSTOMTITLEBAR_H
