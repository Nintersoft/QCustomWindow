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

#include "qcustomtitlebar.h"

QCustomTitleBar::QCustomTitleBar(QWidget *parent) :
    QWidget(parent), FRAME_BUTTON_SIZE(24, 24)
{
    this->mFrameButtons = QCustomAttrs::Close | QCustomAttrs::Maximize | QCustomAttrs::Minimize;

    this->setStyleSheet(QStringLiteral(
        "QPushButton {\n"
        "   border : 0.5px solid gray;\n"
        "   border-radius: 3px;\n"
        "   min-height: 20px;\n"
        "   margin: 1px;\n"
        "   background: white;\n"
        "   color: gray;\n"
        "}\n"
        "QPushButton::hover {\n"
        "   background: darkorange;\n"
        "   border : 0.5px solid darkorange;\n"
        "   color: white;\n"
        "}\n"
        "QPushButton::pressed, QPushButton::!enabled {\n"
        "   background: orange;\n"
        "   border : 0.5px solid orange;\n"
        "   color: white;\n"
        "}\n"
        "QLabel#lblWindowTitle {\n"
        "   margin-left: 8px;\n"
        "}\n"
        "QCustomTitleBar { background: white; }\n"
    ));

    this->lblWindowTitle.setText("QCustomWindow");
    this->lblWindowTitle.setAlignment(Qt::AlignCenter);

    this->btnClose.setText("X");
    this->btnMaximize.setText("+");
    this->btnMinimize.setText("-");

    this->lblWindowIcon.setScaledContents(true);
    this->lblWindowIcon.setMaximumSize(FRAME_BUTTON_SIZE);
    this->lblWindowIcon.setMinimumSize(FRAME_BUTTON_SIZE);
    this->lblWindowIcon.setPixmap(this->windowIcon().pixmap(FRAME_BUTTON_SIZE));

    this->btnClose.setObjectName("btnClose");
    this->btnMaximize.setObjectName("btnMaximize");
    this->btnMinimize.setObjectName("btnMinimize");
    this->lblWindowIcon.setObjectName("lblWindowIcon");
    this->lblWindowTitle.setObjectName("lblWindowTitle");

    this->btnClose.setMaximumSize(FRAME_BUTTON_SIZE);
    this->btnClose.setMinimumSize(FRAME_BUTTON_SIZE);
    this->btnMaximize.setMaximumSize(FRAME_BUTTON_SIZE);
    this->btnMaximize.setMinimumSize(FRAME_BUTTON_SIZE);
    this->btnMinimize.setMaximumSize(FRAME_BUTTON_SIZE);
    this->btnMinimize.setMinimumSize(FRAME_BUTTON_SIZE);

    this->mLayout.addWidget(&this->lblWindowIcon);
    this->mLayout.addWidget(&this->lblWindowTitle, 1);
    this->mLayout.addWidget(&this->btnMinimize);
    this->mLayout.addWidget(&this->btnMaximize);
    this->mLayout.addWidget(&this->btnClose);
    this->mLayout.setContentsMargins(0, 0, 0, 4);
    this->mLayout.setSpacing(0);

    this->setLayout(&this->mLayout);

    connect(&this->btnClose, &QPushButton::clicked, this, [this]{ emit this->closeRequest(); });
    connect(&this->btnMinimize, &QPushButton::clicked, this, [this]{ emit this->minimizeRequest(); });
    connect(&this->btnMaximize, &QPushButton::clicked, this, [this]{ emit this->maximizeRequest(); });

    connect(this, &QWidget::windowTitleChanged, &this->lblWindowTitle, &QLabel::setText);
    connect(this, &QWidget::windowIconChanged, this, [this](const QIcon &icon){
        this->lblWindowIcon.setPixmap(icon.pixmap(FRAME_BUTTON_SIZE));
        this->lblWindowIcon.setVisible(!icon.isNull());
    });

    this->setMaximumHeight(35);
    this->setMinimumHeight(35);
}

void QCustomTitleBar::setWindowButtons(QCustomAttrs::WindowButtons btns){
    this->mFrameButtons = btns;
    this->btnClose.setVisible(btns & QCustomAttrs::Close);
    this->btnMaximize.setVisible(btns & QCustomAttrs::Maximize);
    this->btnMinimize.setVisible(btns & QCustomAttrs::Minimize);
}

void QCustomTitleBar::setWindowButtonText(QCustomAttrs::WindowButton btn, const QString &text){
    switch (btn) {
    case QCustomAttrs::Close: this->btnClose.setText(text); break;
    case QCustomAttrs::Maximize: this->btnMaximize.setText(text); break;
    case QCustomAttrs::Minimize: this->btnMinimize.setText(text); break;
    }
}

void QCustomTitleBar::setWindowButtonEnabled(QCustomAttrs::WindowButton btn, bool enabled){
    switch (btn) {
    case QCustomAttrs::Close: this->btnClose.setEnabled(enabled); break;
    case QCustomAttrs::Maximize: this->btnMaximize.setEnabled(enabled); break;
    case QCustomAttrs::Minimize: this->btnMinimize.setEnabled(enabled); break;
    }
}

void QCustomTitleBar::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) emit changeWindowPositionRequest(event->globalPos());
    QWidget::mouseMoveEvent(event);
}

void QCustomTitleBar::mousePressEvent(QMouseEvent *event){
    if (event->button() & Qt::LeftButton) emit startWindowMoveRequest(event->globalPos());
    QWidget::mousePressEvent(event);
}

void QCustomTitleBar::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() & Qt::LeftButton) emit stopWindowMoveRequest();
    QWidget::mouseReleaseEvent(event);
}

void QCustomTitleBar::mouseDoubleClickEvent(QMouseEvent *event){
    if (mFrameButtons & QCustomAttrs::Maximize && btnMaximize.isEnabled()
            && event->buttons() & Qt::LeftButton) {
        emit maximizeRequest();
    }
    QWidget::mouseDoubleClickEvent(event);
}

void QCustomTitleBar::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}
