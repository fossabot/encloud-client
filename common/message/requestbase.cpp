#include "requestbase.h"

RequestBase::RequestBase()
{

}

const QString &RequestBase::getToken() const
{
    return token;
}

void RequestBase::setToken(const QString &newToken)
{
    token = newToken;
}
