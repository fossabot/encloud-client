#include "loginresponse.h"

LoginResponse::LoginResponse()
{

}

const QString &LoginResponse::getToken() const
{
    return token;
}

void LoginResponse::setToken(const QString &newToken)
{
    token = newToken;
}

const Account &LoginResponse::getAccount() const
{
    return account;
}

void LoginResponse::setAccount(const Account &newAccount)
{
    account = newAccount;
}


