#pragma once

#include "common/globalmarco.h"
class MessageManager;
class LoginRequest{
    friend class MessageManager;
public:
    explicit LoginRequest();
    const QString &getAccount() const;
    void setAccount(const QString &newAccount);


    const QByteArray &getPassword() const;
    void setPassword(const QByteArray &newPassword);

private:
    QString         account;
    QByteArray      password;
signals:

};

