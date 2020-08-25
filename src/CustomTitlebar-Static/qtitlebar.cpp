#include "qtitlebar.h"

QTitleBar::QTitleBar(QMainWindow *parent) :
    QWidget(parent), FRAME_BUTTON_SIZE(24, 24)
{
    this->canMove = false;
    this->maximizing = false;
    this->m_frameButtons = QCustomAttrs::All;

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
        "QTitleBar { background: white; }\n"
    ));

    if (!parent) throw std::exception("Parent must be a QCustomWindow object (cannot be null).");
    this->m_parentWindow = parent;

    this->lbl_windowTitle.setText("QCustomWindow");
    this->lbl_windowTitle.setAlignment(Qt::AlignCenter);

    this->btn_close.setText("X");
    this->btn_maximize.setText("+");
    this->btn_minimize.setText("-");

    this->btn_close.setMaximumSize(FRAME_BUTTON_SIZE);
    this->btn_close.setMinimumSize(FRAME_BUTTON_SIZE);
    this->btn_maximize.setMaximumSize(FRAME_BUTTON_SIZE);
    this->btn_maximize.setMinimumSize(FRAME_BUTTON_SIZE);
    this->btn_minimize.setMaximumSize(FRAME_BUTTON_SIZE);
    this->btn_minimize.setMinimumSize(FRAME_BUTTON_SIZE);

    this->m_layout.addWidget(&this->lbl_windowTitle, 1);
    this->m_layout.addWidget(&this->btn_minimize);
    this->m_layout.addWidget(&this->btn_maximize);
    this->m_layout.addWidget(&this->btn_close);
    this->m_layout.setContentsMargins(0, 0, 0, 4);
    this->m_layout.setSpacing(0);

    this->setLayout(&this->m_layout);

    connect(&this->btn_close, &QPushButton::clicked, [this]{ emit this->requestClose(); });
    connect(&this->btn_minimize, &QPushButton::clicked, [this]{ emit this->requestMinimize(); });
    connect(&this->btn_maximize, &QPushButton::clicked, [this]{ emit this->requestMaximize(); });

    connect(this, &QWidget::windowTitleChanged, &this->lbl_windowTitle, &QLabel::setText);

    this->setMaximumHeight(35);
    this->setMinimumHeight(35);
}

void QTitleBar::setWindowButtons(QCustomAttrs::WindowButtons btns){
    this->m_frameButtons = btns;
    this->btn_close.setVisible(btns & QCustomAttrs::Close);
    this->btn_maximize.setVisible(btns & QCustomAttrs::Maximize);
    this->btn_minimize.setVisible(btns & QCustomAttrs::Minimize);
}

void QTitleBar::setWindowButtonEnabled(QCustomAttrs::WindowButton btn, bool enabled){
    if (btn & QCustomAttrs::Close) this->btn_close.setEnabled(enabled);
    if (btn & QCustomAttrs::Maximize) this->btn_maximize.setEnabled(enabled);
    if (btn & QCustomAttrs::Minimize) this->btn_minimize.setEnabled(enabled);
}

void QTitleBar::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void QTitleBar::mousePressEvent(QMouseEvent *event){
    if (event->button() & Qt::LeftButton){
        this->canMove = (event->x() > 5 && event->y() > 5 && event->x() < (this->m_parentWindow->width() - 5));
        this->m_pCursor = event->globalPos() - this->m_parentWindow->geometry().topLeft();
    }
    QWidget::mousePressEvent(event);
}

void QTitleBar::mouseMoveEvent(QMouseEvent *event){
    if (!this->maximizing && canMove && event->buttons() & Qt::LeftButton
            && !this->m_parentWindow->isMaximized()) this->m_parentWindow->move(event->globalPos() - m_pCursor);
    this->maximizing = false;
    QWidget::mouseMoveEvent(event);
}

void QTitleBar::mouseDoubleClickEvent(QMouseEvent *event){
    if (m_frameButtons & QCustomAttrs::Maximize && btn_maximize.isEnabled()
            && event->buttons() & Qt::LeftButton) {
        this->maximizing = true;
        emit requestMaximize();
    }
    QWidget::mouseDoubleClickEvent(event);
}
