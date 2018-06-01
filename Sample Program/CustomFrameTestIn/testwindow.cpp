#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    NMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    // Sets the custom Widgets on the parent Class
    // Otherwise, the window resizing feature will not work
    NMainWindow::setCustomWidgets(ui->centralWidget, ui->statusBar);

    clicks = 0;
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(clickMePressed()));
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::clickMePressed(){
    clicks ++;
    setWindowTitle("Number of clicks : " + QString::number(clicks));
}
