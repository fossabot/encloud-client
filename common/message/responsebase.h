#pragma once

#include "common/globalmarco.h"
class MessageManager;
class ResponseBase{
    friend class MessageManager;
public:
    ResponseBase();
    qint8 getStatusCode() const;
    void setStatusCode(qint8 newStatusCode);
    const QDateTime &getDate() const;
    void setDate(const QDateTime &newDate);
    const QString &getServerMessage() const;
    void setServerMessage(const QString &newServerMessage);

protected:
    qint8       statusCode;
    QDateTime       date;
    QString     serverMessage;
};

