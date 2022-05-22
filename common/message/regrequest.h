#pragma once

#include "common/globalmarco.h"
class MessageManager;
class RegRequest{
    friend class MessageManager;
public:
    explicit RegRequest();
    const QString &getUserName() const;
    void setUserName(const QString &newUserName);
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);
    const QString &getEmail() const;
    void setEmail(const QString &newEmail);
    const QString &getAccountName() const;
    void setAccountName(const QString &newAccountName);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);
    const QString &getCheckCode() const;
    void setCheckCode(const QString &newCheckCode);
    const QByteArray &getMainKey() const;
    void setMainKey(const QByteArray &newMainKey);
    const QByteArray &getPublicKey() const;
    void setPublicKey(const QByteArray &newPublicKey);
    const QByteArray &getPrivateKey() const;
    void setPrivateKey(const QByteArray &newPrivateKey);

private:
    QString     userName;
    QString     phone;
    QString     email;
    QString     accountName;
    QString     password;
    QString     checkCode;
    QByteArray  mainKey;
    QByteArray  publicKey;
    QByteArray  privateKey;
signals:

};

