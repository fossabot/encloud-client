#include "loginrequest.h"

LoginRequest::LoginRequest()
{

}

const QString &LoginRequest::getAccount() const
{
    return account;
}

void LoginRequest::setAccount(const QString &newAccount)
{
    account = newAccount;
}

const QByteArray &LoginRequest::getPassword() const
{
    return password;
}

void LoginRequest::setPassword(const QByteArray &newPassword)
{
    password = newPassword;
}


