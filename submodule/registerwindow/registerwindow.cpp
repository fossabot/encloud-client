#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "common/message/regrequest.h"
#include "common/networkmanager.h"
#include "common/messagemanager.h"
#include "common/cryptographymanager.h"
#include "common/globaldatamanager.h"
#include "submodule/registerwindow/checkcodelabel.h"
#include <QStyleOption>
#include <QPainter>
#include <QJsonObject>
#include <QImage>
#include <QMessageBox>
#include <QDebug>

RegisterWindow::RegisterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    //窗体初始化
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    //初始化验证码部件
    CheckCodeLabel *checkCodeLabel = new CheckCodeLabel(this);
    ui->checkBoxWg->layout()->addWidget(checkCodeLabel);

    //配置注册事件
    connect(ui->regBtn, &QToolButton::clicked,
            this, &RegisterWindow::registrationProcess);

    //配置取消事件
    connect(ui->cancelBtn, &QToolButton::clicked, [this](){
        this->close();
    });

}

RegisterWindow::~RegisterWindow(){
    delete ui;
}

void RegisterWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void RegisterWindow::registrationProcess()
{
    //初始化
    MessageManager *msgMgr =  MessageManager::self();
    NetworkManager *netMgr =  NetworkManager::self();
    CryptographyManager* crytoMgr = CryptographyManager::self();
    QString userName = ui->userNameLied->text();
    QString phone = ui->phoneLied->text();
    QString email = ui->emailLied->text();
    QString accountName = ui->accountNameLid->text();
    QString accountPassword1 = ui->password1stLied->text();
    QString accountPassword2 = ui->password2stLied->text();
    QString checkCode = ui->chekCodeLied->text();

    //检查必填项是否填充
    if(userName.isEmpty()
            || accountName.isEmpty()
            || accountPassword1.isEmpty()
            || accountPassword2.isEmpty()
            || checkCode.isEmpty())
    {
       QMessageBox::critical(this, "客户端错误", "含有必填项缺失，请重新输入","好的");
       return;
    }

    //二次检查密码是否正确
    if(accountPassword1 != accountPassword2){
        QMessageBox::critical(this,
                              QString("客户端错误"),
                              QString("二次验证密码错误, 请检查输入！"),
                              QString("OK"));
        return;
    }


    //秘钥生成与处理
    KeyPair keyPair =
            crytoMgr->asyKeyGenerate(CryptographyManager::RSA_1024);

    QByteArray mainKey =
            crytoMgr->symKeyGenerate(CryptographyManager::AES_128_ECB);

    QByteArray privateKey_with_encryption =
            crytoMgr->symEncipher(CryptographyManager::AES_128_ECB,
                                  &keyPair.second, &mainKey, NULL);

    QByteArray password_with_padding =
            accountPassword1.toUtf8().append(16-accountPassword1.size(),'\0');


    QByteArray mainKye_with_encryption =
            crytoMgr->symEncipher(CryptographyManager::AES_128_ECB,
                                 &mainKey, &password_with_padding, NULL);

    QByteArray password_with_encryption =
            crytoMgr->calcHashCode(CryptographyManager::MD5, &password_with_padding);

    //获取注册报文
    RegRequest regInfo;
    regInfo.setUserName(userName);
    regInfo.setPhone(phone);
    regInfo.setEmail(email);
    regInfo.setAccountName(accountName);
    regInfo.setPassword(QString(password_with_encryption.toBase64()));
    regInfo.setCheckCode(checkCode);
    regInfo.setMainKey(mainKye_with_encryption.toBase64());
    regInfo.setPublicKey(keyPair.first);
    regInfo.setPrivateKey(privateKey_with_encryption.toBase64());
    QJsonValue jsonValue = msgMgr->getRegRequestJson(&regInfo);

    //发送注册请求
    Reply * reply = netMgr->sendJson(QUrl(REGISTRATION_PATH), jsonValue);
    connect(reply, &Reply::readyReadJson, [this,msgMgr,reply](QJsonValue response){
        RegResponse regResponse;
        msgMgr->phraseRegResponseJson(&response, &regResponse);
        if(regResponse.getStatusCode() == CHECK_CODE_ERROR){
            reply->deleteLater();
            QMessageBox::critical(this,"客户端错误","验证码错误,请重新输入或更换验证码","好的");
        }
        if(regResponse.getStatusCode() == REGISTRATION_SUCCESS){
            reply->deleteLater();
            auto pair = qMakePair(ui->accountNameLid->text(),
                                  ui->password1stLied->text());
            emit this->registrationSuccess(pair);
            this->close();
        }
    });
}

