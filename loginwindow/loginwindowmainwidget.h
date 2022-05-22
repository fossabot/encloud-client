#pragma once

#include "common/globalmarco.h"
#include <QWidget>

namespace Ui {
class LoginWindowMainWidget;
}

class LoginWindowMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindowMainWidget(QWidget *parent = nullptr);
    ~LoginWindowMainWidget();

public:
    QString getAccountName();
    void setAccountName(QString accountName);
    void setAccountPassword(QString accountPassword);
    QString getAccountPassword();
    qint8 isAutoLoginChecked();
    qint8 isRecordPasswdChecked();

signals:
    void loginClicked();
    void restorePasswdClicked(bool checked=false);
private:
    Ui::LoginWindowMainWidget *ui;
};

