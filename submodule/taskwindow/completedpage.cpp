#include "completedpage.h"
#include "ui_completedpage.h"

CompletedPage::CompletedPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompletedPage)
{
    ui->setupUi(this);
}

CompletedPage::~CompletedPage()
{
    delete ui;
}
