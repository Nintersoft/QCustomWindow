#include "qcustomwindow.h"

QCustomWindow::QCustomWindow(QWidget *parent) :
    QMainWindow(parent), RESIZE_LIMIT(4)
{
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);

    this->setMinimumSize(QSize(256, 64));
    this->setStyleSheet(QStringLiteral(
        "\nQCustomWindow {\n"
        "   background : white;\n"
        "   border : 1px solid orange;\n"
        "}\n"
        "QStatusBar {\n"
        "   background : white;\n"
        "   border-bottom: 1px solid orange;\n"
        "   border-left: 1px solid orange;\n"
        "   border-right: 1px solid orange;\n"
        "}\n"
        "QToolBar {\n"
        "    margin : 1px;\n"
        "}"
    ));

    this->m_titleBar = new QTitleBar(this);
    connect(this->m_titleBar, &QTitleBar::requestClose,
            this, &QCustomWindow::close);
    connect(this->m_titleBar, &QTitleBar::requestMaximize, [this]{
        if (this->isMaximized()) this->showNormal();
        else this->showMaximized();
    });
    connect(this->m_titleBar, &QTitleBar::requestMinimize,
            this, &QCustomWindow::showMinimized);
    connect(this, &QMainWindow::windowTitleChanged, this->m_titleBar,
            &QWidget::setWindowTitle);

    this->m_titleBarW = new QWidget();
    this->m_titleBarW->setMouseTracking(true);
    this->m_titleBarW->installEventFilter(this);

    QVBoxLayout *titleLayout = new QVBoxLayout();
    titleLayout->setContentsMargins(6, 6, 6, 0);
    titleLayout->setSpacing(0);
    titleLayout->addWidget(this->m_titleBar);

    this->m_titleBarW->setLayout(titleLayout);
    QMainWindow::setMenuWidget(this->m_titleBarW);

    this->m_leftBorder = generateBorder(Qt::LeftToolBarArea, Qt::Vertical);
    this->m_rightBorder = generateBorder(Qt::RightToolBarArea, Qt::Vertical);
    this->m_bottomBorder = generateBorder(Qt::BottomToolBarArea, Qt::Horizontal);

    this->m_menuBar = nullptr;
    this->m_menuWidget = nullptr;
}

QCustomWindow::~QCustomWindow(){
    delete this->m_titleBar;
    delete this->m_leftBorder;
    delete this->m_rightBorder;
    delete this->m_bottomBorder;

    if (this->m_menuBar) delete this->m_menuBar;
    else if (this->m_menuWidget) delete this->m_menuWidget;
}

QToolBar *QCustomWindow::generateBorder(Qt::ToolBarArea area,
                                        Qt::Orientation orientation){
    QToolBar *border = new QToolBar("___border___");
    border->setStyleSheet(
        "\nQToolBar {\n"
        "   margin : 1px;\n"
        "   border : 0px;\n"
        "   background : transparent;\n"
        "}"
    );

    if (orientation & Qt::Horizontal){
        border->setMinimumHeight(6);
        border->setMaximumHeight(6);
    }
    else {
        border->setMinimumWidth(6);
        border->setMaximumWidth(6);
    }
    border->setMovable(false);
    border->setFloatable(false);
    border->setAllowedAreas(area);
    border->setMouseTracking(true);
    border->installEventFilter(this);

    this->addToolBar(area, border);
    return border;
}

QMenu * QCustomWindow::createPopupMenu(){
    QMenu *menu = QMainWindow::createPopupMenu();
    QList<QAction *> removal;
    foreach (QAction *a, menu->actions())
        if (a->text() == "___border___") removal.append(a);
    foreach (QAction *a, removal) menu->removeAction(a);
    return menu;
}

void QCustomWindow::setMenuBar(QMenuBar *menuBar){
    if (this->m_menuBar == menuBar) return;

    if (this->m_menuBar) {
        if (this->m_menuBar != this->m_menuWidget && this->m_menuWidget){
            this->m_menuWidget->setParent(nullptr);
            this->m_menuWidget->deleteLater();
        }

        this->m_menuBar->hide();
        this->m_menuBar->setParent(nullptr);
        this->m_menuBar->deleteLater();
    }

    this->m_menuBar = menuBar;
    this->m_menuWidget = qobject_cast<QWidget *>(menuBar);

    if (menuBar){
        menuBar->setParent(this);
        this->m_titleBarW->layout()->addWidget(menuBar);
    }
}

QMenuBar* QCustomWindow::menuBar() const{
    return this->m_menuBar;
}

void QCustomWindow::setMenuWidget(QWidget *widget){
    if (this->m_menuWidget == widget) return;

    widget->setParent(this);

    if (this->m_menuWidget){
        this->m_menuWidget->hide();
        this->m_menuWidget->setParent(nullptr);
        this->m_menuWidget->deleteLater();
    }

    this->m_menuBar = nullptr;
    this->m_menuWidget = widget;

    if (this->m_menuWidget){
        this->m_menuWidget->setParent(this);
        this->m_titleBarW->layout()->addWidget(widget);
    }
}

QWidget * QCustomWindow::menuWidget() const{
    return this->m_menuWidget;
}

bool QCustomWindow::eventFilter(QObject*, QEvent *event){
    if (event->type() == QEvent::MouseMove)
        customMouseMoveEvent(static_cast<QMouseEvent*>(event));
    else if (event->type() == QEvent::MouseButtonPress)
        mousePressEvent(static_cast<QMouseEvent*>(event));
    return false;
}

bool QCustomWindow::event(QEvent *event){
    if (event->type() == QEvent::ChildRemoved){
        QChildEvent *evt = static_cast<QChildEvent*>(event);
        if (evt->child()->isWidgetType()) evt->child()->removeEventFilter(this);
    }
    else if (event->type() == QEvent::ChildAdded){
        QChildEvent *evt = static_cast<QChildEvent*>(event);
        if (evt->child()->isWidgetType()){
            QWidget *child = qobject_cast<QWidget*>(evt->child());

            child->setMouseTracking(true);
            child->installEventFilter(this);

            if (child->metaObject()->indexOfClassInfo("custom_obj_type") == -1){
                child->setStyleSheet(child->styleSheet() +
                                     "\nQToolBar {\n"
                                     "    margin : 1px;\n"
                                     "    padding: 0px 6px 0px 6px;\n"
                                     "    border: 1px transparent solid;"
                                     "}\n"
                                     "QToolBar:top:first, QToolBar:bottom:first, QToolBar:left:first {\n"
                                     "    margin : 0px 0px 0px 6px;\n"
                                     "}\n"
                                     "QToolBar:top:only-one, QToolBar:bottom:only-one {\n"
                                     "    margin : 0px 6px 0px 6px;\n"
                                     "}\n"
                                     "QToolBar:top:last, QToolBar:bottom:last, QToolBar:right:last {\n"
                                     "    margin : 0px 6px 0px 0px;\n"
                                     "}\n");
            }
        }
    }
    return QMainWindow::event(event);
}

void QCustomWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() & Qt::LeftButton){
        int x = event->x(), y = event->y();
        int bottom = this->height() - RESIZE_LIMIT, right = this->width() - RESIZE_LIMIT;

        QPoint posCursor = event->globalPos();
        Qt::Edges nFlags = {};
        if (x < RESIZE_LIMIT) {
            nFlags |= Qt::LeftEdge;
            posCursor.rx() -= this->x();
        }
        if (y < RESIZE_LIMIT) {
            nFlags |= Qt::TopEdge;
            posCursor.ry() -= this->y();
        }
        if (x > right) {
            nFlags |= Qt::RightEdge;
            posCursor.rx() -= (this->x() + this->width());
        }
        if (y > bottom) {
            nFlags |= Qt::BottomEdge;
            posCursor.ry() -= (this->y() + this->height());
        }
        this->m_lock = nFlags;
        this->m_posCursor = posCursor;
    }
    QMainWindow::mousePressEvent(event);
}

void QCustomWindow::mouseReleaseEvent(QMouseEvent *event){
    this->m_lock = {};
    this->unsetCursor();
    QMainWindow::mouseMoveEvent(event);
}

void QCustomWindow::customMouseMoveEvent(QMouseEvent *event){
    if (this->m_lock){
        QPoint tL = this->geometry().topLeft(), bR = this->geometry().bottomRight();
        if (this->m_lock & Qt::TopEdge) tL.ry() = event->globalY() - this->m_posCursor.y();
        if (this->m_lock & Qt::BottomEdge) bR.ry() = event->globalY() - this->m_posCursor.y();
        if (this->m_lock & Qt::LeftEdge) tL.rx() = event->globalX() - this->m_posCursor.x();
        if (this->m_lock & Qt::RightEdge) bR.rx() = event->globalX() - this->m_posCursor.x();
        this->setGeometry(QRect(tL, bR));
        return;
    }

    int x = event->globalX() - this->x(), y = event->globalY() - this->y();
    int bottom = this->height() - RESIZE_LIMIT, right = this->width() - RESIZE_LIMIT;

    if (x < RESIZE_LIMIT){
        if (y < RESIZE_LIMIT) this->setCursor(QCursor(Qt::SizeFDiagCursor));
        else if (y > bottom) this->setCursor(QCursor(Qt::SizeBDiagCursor));
        else this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (x > right){
        if (y < RESIZE_LIMIT) this->setCursor(QCursor(Qt::SizeBDiagCursor));
        else if (y > bottom) this->setCursor(QCursor(Qt::SizeFDiagCursor));
        else this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (y < RESIZE_LIMIT || y > bottom) this->setCursor(Qt::SizeVerCursor);
    else this->unsetCursor();
}
