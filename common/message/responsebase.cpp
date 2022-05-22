#include "responsebase.h"

ResponseBase::ResponseBase()
{

}

qint8 ResponseBase::getStatusCode() const
{
    return statusCode;
}

void ResponseBase::setStatusCode(qint8 newStatusCode)
{
    statusCode = newStatusCode;
}

const QDateTime &ResponseBase::getDate() const
{
    return date;
}

void ResponseBase::setDate(const QDateTime &newDate)
{
    date = newDate;
}

const QString &ResponseBase::getServerMessage() const
{
    return serverMessage;
}

void ResponseBase::setServerMessage(const QString &newServerMessage)
{
    serverMessage = newServerMessage;
}
