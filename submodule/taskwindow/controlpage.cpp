#include "controlpage.h"
#include "ui_controlpage.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QProgressBar>
ControlPage::ControlPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UploadControlPage)
{
    ui->setupUi(this);
    QProgressBar *bar =  new QProgressBar();
    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setText(0,"java大全");
    ui->treeWidget->addTopLevelItem(item);
    ui->treeWidget->setItemWidget(item,3,bar);
}

ControlPage::~ControlPage()
{
    delete ui;
}
