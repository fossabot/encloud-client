#pragma once

#include "common/globalmarco.h"
#include "common/entity/account.h"
#include "common/globalmarco.h"
#include "common/entity/account.h"
#include "common/message/responsebase.h"
class MessageManager;
class LoginResponse : public ResponseBase{
    friend class MessageManager;
public:
    explicit LoginResponse();

    const QString &getToken() const;
    void setToken(const QString &newToken);

    const Account &getAccount() const;
    void setAccount(const Account &newAccount);

private:
    QString     token;
    Account     account;
signals:

};

