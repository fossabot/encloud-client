#include "loginwelcomewidget.h"
#include "ui_loginwelcomewidget.h"

LoginWelcomeWidget::LoginWelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWelcomeWidget)
{
    ui->setupUi(this);
}

LoginWelcomeWidget::~LoginWelcomeWidget(){
    delete ui;
}
