#ifndef QCUSTOMWINDOW_H
#define QCUSTOMWINDOW_H

#include <QMenu>
#include <QRect>
#include <QPoint>
#include <QObject>
#include <QWidget>
#include <QCursor>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMetaMethod>
#include <QMetaObject>
#include <QDockWidget>
#include <QMainWindow>
#include <QMouseEvent>
#include <QVBoxLayout>

#include "qtitlebar.h"

class QCustomWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QCustomWindow(QWidget *parent = nullptr);
    ~QCustomWindow() override;

    QMenu * createPopupMenu() override;

    void setMenuBar(QMenuBar *menuBar);
    QMenuBar * menuBar() const;

    void setMenuWidget(QWidget *widget);
    QWidget * menuWidget() const;

    inline QTitleBar& titleBar() const { return *this->m_titleBar; }

protected:
    const int RESIZE_LIMIT;

    bool event(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

    void customMouseMoveEvent(QMouseEvent* event);

private:
    bool init;

    QWidget *m_titleBarW;
    QWidget *m_menuWidget;
    QMenuBar *m_menuBar;
    QTitleBar *m_titleBar;

    QToolBar *m_leftBorder;
    QToolBar *m_rightBorder;
    QToolBar *m_bottomBorder;

    Qt::Edges m_lock;
    QPoint m_posCursor;

    QToolBar * generateBorder(Qt::ToolBarArea area, Qt::Orientation orientation);
};

#endif // QCUSTOMWINDOW_H
