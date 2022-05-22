#pragma once

#include "common/globalmarco.h"
#include "common/entity/user.h"
#include "common/message/responsebase.h"
class MessageManager;
class UserSyncResponse : public ResponseBase{
    friend class MessageManager;
public:
    UserSyncResponse();
    const User &getUser() const;
    void setUser(const User &newUser);

private:
    User        user;
};

