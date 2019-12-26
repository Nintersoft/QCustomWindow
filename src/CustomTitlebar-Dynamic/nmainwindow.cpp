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

#include "nmainwindow.h"
#include "ui_nmainwindow.h"

NMainWindow::NMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NMainWindow),
    RESIZE_LIMIT(2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    centralWidget()->installEventFilter(this);
    ui->titleBar->installEventFilter(this);
    ui->statusBar->installEventFilter(this);

    centralWidget()->setMouseTracking(true);
    ui->titleBar->setMouseTracking(true);
    ui->statusBar->setMouseTracking(true);

    setWindowTitle("Custom Window Border");
    locked = LockMoveType::None;

    ui->headerWidget->setTitleBarWidget(ui->titleBar);
    if (ui->titleBar->mainWindow() != this)
        ui->titleBar->setMainWindow(this);

    if (this->maximumSize() == this->minimumSize())
        setMaximizeButtonEnabled(false);

    connect(ui->titleBar, &TitleBar::closeRequest, this, &NMainWindow::close);
}

NMainWindow::~NMainWindow()
{
    delete ui;
}

void NMainWindow::setCustomWidgets(QWidget *newCentralWidget, QStatusBar *newStatusBar){
    setCustomStatusBar(newStatusBar);
    setNewCentralWidget(newCentralWidget);
}

void NMainWindow::setCustomStatusBar(QStatusBar *newStatusBar){
    if (!newStatusBar) return;
    newStatusBar->installEventFilter(this);
    newStatusBar->setMouseTracking(true);
}

void NMainWindow::setNewCentralWidget(QWidget *newCentralWidget){
    if (!newCentralWidget) return;
    newCentralWidget->installEventFilter(this);
    newCentralWidget->setMouseTracking(true);

    if (newCentralWidget->layout())
        newCentralWidget->layout()->setContentsMargins(10, 0, 10, 0);
}

void NMainWindow::setCloseButtonEnabled(bool enable){
    ui->titleBar->setCloseButtonEnabled(enable);
}

void NMainWindow::setMaximizeButtonEnabled(bool enable){
    ui->titleBar->setMaximizeButtonEnabled(enable);
}

void NMainWindow::setMinimizeButtonEnabled(bool enable){
    ui->titleBar->setMinimizeButtonEnabled(enable);
}

void NMainWindow::setTitlebarStylesheet(const QString &styleSheet){
    ui->titleBar->setStyleSheet(styleSheet);
}

QString NMainWindow::titlebarStylesheet() const {
    return ui->titleBar->styleSheet();
}

void NMainWindow::closeEvent(QCloseEvent *event){
    if (event->isAccepted()) QMainWindow::closeEvent(event);
    else event->ignore();
}

/*
 * GUI Protected Methods (do not change them, unless it's really necessary)
 */

void NMainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        int x = event->x(), y = event->y(), bottom = this->height() - RESIZE_LIMIT, right = this->width() - RESIZE_LIMIT;
        if (x < RESIZE_LIMIT && y < RESIZE_LIMIT){
            posCursor = event->globalPos() - this->geometry().topLeft();
            locked = LockMoveType::TopLeft;
        }
        else if (x < RESIZE_LIMIT && y > bottom){
            posCursor = event->globalPos() - this->geometry().bottomLeft();
            locked = LockMoveType::BottomLeft;
        }
        else if (x > right && y < RESIZE_LIMIT){
            posCursor = event->globalPos() - this->geometry().topRight();
            locked = LockMoveType::TopRight;
        }
        else if (x > right && y > bottom){
            posCursor = event->globalPos() - this->geometry().bottomRight();
            locked = LockMoveType::BottomRight;
        }
        else if (x < RESIZE_LIMIT || y < RESIZE_LIMIT){
            posCursor = event->globalPos() - this->geometry().topLeft();
            locked = x < RESIZE_LIMIT ? LockMoveType::Left : LockMoveType::Top;
        }
        else if (x > right || y > bottom){
            posCursor = event->globalPos() - this->geometry().bottomRight();
            locked = x > right ? LockMoveType::Right : LockMoveType::Bottom;
        }
        event->accept();
    }
}

void NMainWindow::undefMouseMoveEvent(QObject* object, QMouseEvent* event){
    if (locked != LockMoveType::None){
        switch (locked) {
        case LockMoveType::TopLeft:
            this->setGeometry(QRect(QPoint(event->globalPos().x() - posCursor.x(), event->globalPos().y() - posCursor.y()),
                                    this->geometry().bottomRight()));
            break;
        case LockMoveType::TopRight:
            this->setGeometry(QRect(QPoint(this->geometry().left(), event->globalPos().y() - posCursor.y()),
                                    QPoint(event->globalPos().x() - posCursor.x(), this->geometry().bottom())));
            break;
        case LockMoveType::BottomLeft:
            this->setGeometry(QRect(QPoint(event->globalPos().x() - posCursor.x(), this->geometry().top()),
                                    QPoint(this->geometry().right(), event->globalPos().y() - posCursor.y())));
            break;
        case LockMoveType::BottomRight:
            this->setGeometry(QRect(this->geometry().topLeft(),
                                    QPoint(event->globalPos().x() - posCursor.x(), event->globalPos().y() - posCursor.y())));
            break;
        case LockMoveType::Left:
            this->setGeometry(QRect(QPoint(event->globalPos().x() - posCursor.x(), this->geometry().top()),
                                    this->geometry().bottomRight()));
            break;
        case LockMoveType::Right:
            this->setGeometry(QRect(this->geometry().topLeft(),
                                    QPoint(event->globalPos().x() - posCursor.x(), this->geometry().bottom())));
            break;
        case LockMoveType::Top:
            this->setGeometry(QRect(QPoint(this->geometry().left(), event->globalPos().y() - posCursor.y()),
                                    this->geometry().bottomRight()));
            break;
        default:
            this->setGeometry(QRect(this->geometry().topLeft(),
                                    QPoint(this->geometry().right(), event->globalPos().y() - posCursor.y())));
            break;
        }
        return;
    }

    int x = event->x(), y = event->y(), right = this->width() - RESIZE_LIMIT;
    if (object->objectName() == "statusBar"){
        if (x < RESIZE_LIMIT && y > (19 - RESIZE_LIMIT)){
            this->setCursor(QCursor(Qt::SizeBDiagCursor));
            return;
        }
        else if (x > right && y > (19 - RESIZE_LIMIT)){
            this->setCursor(QCursor(Qt::SizeFDiagCursor));
            return;
        }
        else if (y > (19 - RESIZE_LIMIT)){
            this->setCursor(QCursor(Qt::SizeVerCursor));
            return;
        }
    }
    else if (object->objectName() == "titleBar"){
        if (x < RESIZE_LIMIT && y < RESIZE_LIMIT){
            this->setCursor(QCursor(Qt::SizeFDiagCursor));
            return;
        }
        if (x > right && y < RESIZE_LIMIT){
            this->setCursor(QCursor(Qt::SizeBDiagCursor));
            return;
        }
        else if (y < RESIZE_LIMIT){
            this->setCursor(QCursor(Qt::SizeVerCursor));
            return;
        }
    }

    this->setCursor(QCursor(x < RESIZE_LIMIT || x > right ? Qt::SizeHorCursor : Qt::ArrowCursor));
}

void NMainWindow::mouseReleaseEvent(QMouseEvent *event){
    locked = LockMoveType::None;
    event->accept();
}

bool NMainWindow::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::MouseMove)
        undefMouseMoveEvent(object, static_cast<QMouseEvent*>(event));
    else if (event->type() == QEvent::MouseButtonPress && object->objectName() == "titleBar")
        mousePressEvent(static_cast<QMouseEvent*>(event));
    return false;
}
