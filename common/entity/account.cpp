#include "account.h"

Account::Account()
{

}

qint64 Account::getAccountID() const
{
    return accountID;
}

void Account::setAccountID(qint64 newAccountID)
{
    accountID = newAccountID;
}

const QString &Account::getAccountName() const
{
    return accountName;
}

void Account::setAccountName(const QString &newAccountName)
{
    accountName = newAccountName;
}

const QImage &Account::getPicture() const
{
    return picture;
}

void Account::setPicture(const QImage &newPicture)
{
    picture = newPicture;
}

const QDateTime &Account::getCreateDate() const
{
    return createDate;
}

void Account::setCreateDate(const QDateTime &newCreateDate)
{
    createDate = newCreateDate;
}

const QByteArray &Account::getMainKey() const
{
    return mainKey;
}

void Account::setMainKey(const QByteArray &newMainKey)
{
    mainKey = newMainKey;
}

const QByteArray &Account::getPublicKey() const
{
    return publicKey;
}

void Account::setPublicKey(const QByteArray &newPublicKey)
{
    publicKey = newPublicKey;
}

const QByteArray &Account::getPrivateKey() const
{
    return privateKey;
}

void Account::setPrivateKey(const QByteArray &newPrivateKey)
{
    privateKey = newPrivateKey;
}

qint64 Account::getUserID() const
{
    return userID;
}

void Account::setUserID(qint64 newUserID)
{
    userID = newUserID;
}

const QByteArray &Account::getPassword() const
{
    return password;
}

void Account::setPassword(const QByteArray &newPassword)
{
    password = newPassword;
}

const QString &Account::getRootDirID() const
{
    return rootDirID;
}

void Account::setRootDirID(const QString &newRootDirID)
{
    rootDirID = newRootDirID;
}
