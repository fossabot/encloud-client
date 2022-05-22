#pragma once

#include "common/globalmarco.h"
#include "common/entity/account.h"
#include "common/message/responsebase.h"

class MessageManager;
class AccountSyncResponse : public ResponseBase{
    friend class MessageManager;
public:
    AccountSyncResponse();
    const Account &getAccount() const;
    void setAccount(const Account &newAccount);

private:
    Account     account;
};

