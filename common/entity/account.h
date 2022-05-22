#pragma once

#include "common/globalmarco.h"
#include <QImage>
#include <QDateTime>

class Account{
public:
    explicit Account();
    qint64 getAccountID() const;
    void setAccountID(qint64 newAccountID);
    const QString &getAccountName() const;
    void setAccountName(const QString &newAccountName);
    const QImage &getPicture() const;
    void setPicture(const QImage &newPicture);
    const QDateTime &getCreateDate() const;
    void setCreateDate(const QDateTime &newCreateDate);
    const QByteArray &getMainKey() const;
    void setMainKey(const QByteArray &newMainKey);
    const QByteArray &getPublicKey() const;
    void setPublicKey(const QByteArray &newPublicKey);
    const QByteArray &getPrivateKey() const;
    void setPrivateKey(const QByteArray &newPrivateKey);
    qint64 getUserID() const;
    void setUserID(qint64 newUserID);
    const QByteArray &getPassword() const;
    void setPassword(const QByteArray &newPassword);
    const QString &getRootDirID() const;
    void setRootDirID(const QString &newRootDirID);

private:
    qint64      accountID;
    QByteArray  password;
    QString     accountName;
    QImage      picture;
    qint64      userID;
    QDateTime   createDate;
    QString     rootDirID;
    QByteArray  mainKey;
    QByteArray  publicKey;
    QByteArray  privateKey;
signals:

};
