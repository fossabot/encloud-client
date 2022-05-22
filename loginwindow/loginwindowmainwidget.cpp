#include "loginwindowmainwidget.h"
#include "ui_loginwindowmainwidget.h"
#include <QToolButton>
#include <QSignalMapper>
LoginWindowMainWidget::LoginWindowMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindowMainWidget)
{
    ui->setupUi(this);
    connect(ui->login, &QToolButton::clicked, [=](){
       emit this->loginClicked();
    });
    connect(ui->restordPasswd, &QToolButton::clicked, [=](bool checked){
       emit this->restorePasswdClicked(checked);
    });

    QSignalMapper * mapper =  new QSignalMapper(this);
    void (QSignalMapper::*map)() = &QSignalMapper::map;
    connect(ui->accountNameInput, &QLineEdit::returnPressed, mapper, map);
    connect(ui->accountPasswdInput,&QLineEdit::returnPressed,mapper,map);
    mapper->setMapping(ui->accountNameInput,1);
    mapper->setMapping(ui->accountPasswdInput,2);
    connect(mapper,&QSignalMapper::mappedInt, [this](){
        emit this->loginClicked();
    });


}

LoginWindowMainWidget::~LoginWindowMainWidget()
{
    delete ui;
}

QString LoginWindowMainWidget::getAccountName()
{
    return ui->accountNameInput->text();
}

void LoginWindowMainWidget::setAccountName(QString accountName)
{
    ui->accountNameInput->setText(accountName);
}

void LoginWindowMainWidget::setAccountPassword(QString accountPassword)
{
    ui->accountPasswdInput->setText(accountPassword);
}

QString LoginWindowMainWidget::getAccountPassword()
{
    return ui->accountPasswdInput->text();
}

qint8 LoginWindowMainWidget::isAutoLoginChecked()
{
    return ui->autoLogin->checkState();
}

qint8 LoginWindowMainWidget::isRecordPasswdChecked()
{
    return ui->recordPasswd->checkState();
}
