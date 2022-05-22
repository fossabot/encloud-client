#include "mainwindowstackwidget.h"
#include "ui_mainwindowstackwidget.h"

MainWindowStackWidget::MainWindowStackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindowStackWidget)
{
    ui->setupUi(this);
}

MainWindowStackWidget::~MainWindowStackWidget(){
    delete ui;
}

void MainWindowStackWidget::setCurrentPage(int indx){
    ui->stackedWidget->setCurrentIndex(indx);
}
