#include "loginwindowsiderwidget.h"
#include "ui_loginwindowsiderwidget.h"

LoginWindowSiderWidget::LoginWindowSiderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindowSiderWidget)
{
    ui->setupUi(this);
    connect(ui->toolButton, &QToolButton::clicked, [=](bool checked){
       emit this->clicked(checked);
    });
}

LoginWindowSiderWidget::~LoginWindowSiderWidget()
{
    delete ui;
}

void LoginWindowSiderWidget::setText(QString str)
{
    ui->toolButton->setText(str);
}
