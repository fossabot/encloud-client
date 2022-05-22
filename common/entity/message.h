#pragma once

#include "common/globalmarco.h"
class Message{
public:
    explicit Message();
    qint64 getMsgID() const;
    void setMsgID(qint64 newMsgID);
    qint64 getMsgSenderID() const;
    void setMsgSenderID(qint64 newMsgSenderID);
    qint64 getMsgReceiverID() const;
    void setMsgReceiverID(qint64 newMsgReceiverID);
    qint64 getMsgTypeID() const;
    void setMsgTypeID(qint64 newMsgTypeID);
    const QString &getMsgContent() const;
    void setMsgContent(const QString &newMsgContent);

private:
    qint64      msgID;
    qint64      msgSenderID;
    qint64      msgReceiverID;
    qint64      msgTypeID;
    QString     msgContent;
signals:

};

