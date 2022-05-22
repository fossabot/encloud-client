#pragma once

#include "common/globalmarco.h"
class MessageManager;
class RequestBase{
    friend class MessageManager;
public:
    RequestBase();
    const QString &getToken() const;
    void setToken(const QString &newToken);

protected:
    QString token;
};

