#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include "nmainwindow.h"

namespace Ui {
class TestWindow;
}

class TestWindow : public NMainWindow
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = 0);
    ~TestWindow();

private:
    Ui::TestWindow *ui;

protected:
    int clicks;

protected slots:
    void clickMePressed();
};

#endif // TESTWINDOW_H
