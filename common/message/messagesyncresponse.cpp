#include "messagesyncresponse.h"

MessageSyncResponse::MessageSyncResponse()
{

}

const QList<Message> &MessageSyncResponse::getMessages() const
{
    return messages;
}

void MessageSyncResponse::setMessages(const QList<Message> &newMessages)
{
    messages = newMessages;
}
