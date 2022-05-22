#include "message.h"

Message::Message()
{

}

qint64 Message::getMsgID() const
{
    return msgID;
}

void Message::setMsgID(qint64 newMsgID)
{
    msgID = newMsgID;
}

qint64 Message::getMsgSenderID() const
{
    return msgSenderID;
}

void Message::setMsgSenderID(qint64 newMsgSenderID)
{
    msgSenderID = newMsgSenderID;
}

qint64 Message::getMsgReceiverID() const
{
    return msgReceiverID;
}

void Message::setMsgReceiverID(qint64 newMsgReceiverID)
{
    msgReceiverID = newMsgReceiverID;
}

qint64 Message::getMsgTypeID() const
{
    return msgTypeID;
}

void Message::setMsgTypeID(qint64 newMsgTypeID)
{
    msgTypeID = newMsgTypeID;
}

const QString &Message::getMsgContent() const
{
    return msgContent;
}

void Message::setMsgContent(const QString &newMsgContent)
{
    msgContent = newMsgContent;
}
