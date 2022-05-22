#include "ui_loginwindow.h"
#include "loginwindow/loginwindow.h"
#include "common/message/loginrequest.h"
#include "common/globaldatamanager.h"
#include "common/cryptographymanager.h"
#include "common/networkmanager.h"
#include "submodule/settingwindow/settingwindow.h"
#include "submodule/registerwindow/registerwindow.h"
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsDropShadowEffect>
#include <QToolButton>
#include <QApplication>
#include <QPainterPath>
#include <QMessageBox>
LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    //设置窗体属性
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setWindowTitle("Login");
    setContextMenuPolicy(Qt::PreventContextMenu);

    //初始化主部件
    connect(ui->mainWg, &LoginWindowMainWidget::loginClicked,
            this, &LoginWindow::loginProcess);

    //初始化注册部件
    ui->regSiderWg->setText("注册账号");
    connect(ui->regSiderWg, &LoginWindowSiderWidget::clicked, [this](){
       RegisterWindow *regwg = new RegisterWindow();
       regwg->setAttribute(Qt::WA_DeleteOnClose);
       regwg->show();
       connect(regwg, &RegisterWindow::registrationSuccess, [=](QPair<QString,QString> pair){
            ui->mainWg->setAccountName(pair.first);
            ui->mainWg->setAccountPassword(pair.second);
       });
    });

    //初始化设置
    ui->settingSiderWg->setText("客户端设置");
    connect(ui->settingSiderWg, &LoginWindowSiderWidget::clicked, [this](){
       SettingWindow *settingwg = new SettingWindow;
       settingwg->setAttribute(Qt::WA_DeleteOnClose);
       settingwg->show();
    });

}

LoginWindow::~LoginWindow(){
    delete ui;
}

void LoginWindow::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}



void LoginWindow::loginProcess(){
    //初始化
    NetworkManager *netMgr = NetworkManager::self();
    CryptographyManager* crytoMgr = CryptographyManager::self();
    MessageManager *msgMgr = MessageManager::self();
    QString accountName =  ui->mainWg->getAccountName();
    QString password = ui->mainWg->getAccountPassword();
    if(accountName.isEmpty() || password.isEmpty()){
        QMessageBox::critical(this, "客户端错误","请输入用户名或密码", "好的");
        return;
    }

    //生成秘钥哈希值
    QByteArray password_with_padding =
            password.toUtf8().append(16-password.size(), '\0');
    QByteArray passwordHashCode = crytoMgr->calcHashCode(
                CryptographyManager::MD5,
                &password_with_padding);
    stdoutput << "登录密码hash值" << passwordHashCode.toBase64();

    //发送登录请求
    LoginRequest loginInfo;
    loginInfo.setAccount(accountName);
    loginInfo.setPassword(passwordHashCode.toBase64());
    QJsonValue loginJson =  msgMgr->getLoginRequestJson(&loginInfo);
    Reply * reply =  netMgr->sendJson(QUrl(LOGIN_PATH),loginJson);
    connect(reply, &Reply::readyReadJson, [this,msgMgr,crytoMgr,reply,password_with_padding](QJsonValue loginResponseJson){
        //解析响应数据
        LoginResponse loginResponse;
        msgMgr->phraseLoginResponseJson(&loginResponseJson, &loginResponse);
        if( loginResponse.getStatusCode() != LOGIN_SUCCESS){
            QMessageBox::critical(this, "服务器错误", "用户名或密码错误","好的");
            return;
        }

        //设置账户数据
        GlobalDataManager* dataMgr =  GlobalDataManager::self();
        dataMgr->setToken(loginResponse.getToken());
        dataMgr->setAccount(loginResponse.getAccount());

        //解密账户秘钥
        QByteArray mainKey_e  = QByteArray::fromBase64(loginResponse.getAccount().getMainKey());
        QByteArray mainKey =
                crytoMgr->symDecipher(CryptographyManager::AES_128_ECB,
                &mainKey_e,
                &password_with_padding,NULL);

        QByteArray privateKey_e = QByteArray::fromBase64(loginResponse.getAccount().getPrivateKey());
        QByteArray privateKey =
                crytoMgr->symDecipher(CryptographyManager::AES_128_ECB,
                &privateKey_e,
                &mainKey,NULL);
        dataMgr->setAccountMainKey(mainKey);
        dataMgr->setAccountPrivateKey(privateKey);

        emit this->loginSuccessfully();
        this->close();
    });
}

