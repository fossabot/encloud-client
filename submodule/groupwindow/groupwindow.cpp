#include "submodule/groupwindow/groupwindow.h"
#include "ui_groupwindow.h"

GroupWindow::GroupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupWindow)
{
    ui->setupUi(this);
}

GroupWindow::~GroupWindow()
{
    delete ui;
}
