#include "regrequest.h"

RegRequest::RegRequest()
{

}

const QString &RegRequest::getUserName() const
{
    return userName;
}

void RegRequest::setUserName(const QString &newUserName)
{
    userName = newUserName;
}

const QString &RegRequest::getPhone() const
{
    return phone;
}

void RegRequest::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

const QString &RegRequest::getEmail() const
{
    return email;
}

void RegRequest::setEmail(const QString &newEmail)
{
    email = newEmail;
}

const QString &RegRequest::getAccountName() const
{
    return accountName;
}

void RegRequest::setAccountName(const QString &newAccountName)
{
    accountName = newAccountName;
}

const QString &RegRequest::getCheckCode() const
{
    return checkCode;
}

void RegRequest::setCheckCode(const QString &newCheckCode)
{
    checkCode = newCheckCode;
}

const QByteArray &RegRequest::getMainKey() const
{
    return mainKey;
}

void RegRequest::setMainKey(const QByteArray &newMainKey)
{
    mainKey = newMainKey;
}

const QByteArray &RegRequest::getPublicKey() const
{
    return publicKey;
}

void RegRequest::setPublicKey(const QByteArray &newPublicKey)
{
    publicKey = newPublicKey;
}

const QByteArray &RegRequest::getPrivateKey() const
{
    return privateKey;
}

void RegRequest::setPrivateKey(const QByteArray &newPrivateKey)
{
    privateKey = newPrivateKey;
}



const QString &RegRequest::getPassword() const
{
    return password;
}

void RegRequest::setPassword(const QString &newPassword)
{
    password = newPassword;
}
