#include "taskwindow.h"
#include "ui_taskwindow.h"


TaskWindow::TaskWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWindow)
{
    ui->setupUi(this);


}

TaskWindow::~TaskWindow()
{
    delete ui;
}
