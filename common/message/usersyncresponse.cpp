#include "usersyncresponse.h"

UserSyncResponse::UserSyncResponse()
{

}

const User &UserSyncResponse::getUser() const
{
    return user;
}

void UserSyncResponse::setUser(const User &newUser)
{
    user = newUser;
}
