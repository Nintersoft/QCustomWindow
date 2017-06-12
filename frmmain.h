#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>

#include "titlebar.h"

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

protected:
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
    Ui::frmMain *ui;
    QPoint posCursor;
    LockMoveType locked;
};

#endif // FRMMAIN_H
