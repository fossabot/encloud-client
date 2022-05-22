#include "accountsyncresponse.h"

AccountSyncResponse::AccountSyncResponse()
{

}

const Account &AccountSyncResponse::getAccount() const
{
    return account;
}

void AccountSyncResponse::setAccount(const Account &newAccount)
{
    account = newAccount;
}
