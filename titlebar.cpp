#include "titlebar.h"
#include "ui_titlebar.h"

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
    this->parent = parent->parentWidget();

    connect(ui->btClose,SIGNAL(clicked()),this->parent,SLOT(close()));
    connect(ui->btMinimize,SIGNAL(clicked()),this->parent,SLOT(showMinimized()));
    connect(ui->btMaximize,SIGNAL(clicked()),this,SLOT(maximizeParent()));

    connect(this->parent, SIGNAL(windowTitleChanged(QString)), ui->lblFormTitle, SLOT(setText(QString)));

    canMove = false;
}

TitleBar::~TitleBar()
{
    delete ui;
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
        parent->move(event->globalPos() - m_pCursor);
        event->accept();
    }
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) maximizeParent();
}

void TitleBar::maximizeParent(){
    if (parent->isMaximized()) parent->showNormal();
    else parent->showMaximized();
}

void TitleBar::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
