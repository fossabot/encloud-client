#include "sharewindow.h"
#include "ui_sharewindow.h"

ShareWindow::ShareWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShareWindow)
{
    ui->setupUi(this);
}

ShareWindow::~ShareWindow()
{
    delete ui;
}
