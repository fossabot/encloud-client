#pragma once

#include "common/globalmarco.h"
#include "common/entity/message.h"
#include "common/message/responsebase.h"
class MessageManager;
class MessageSyncResponse : public ResponseBase{
    friend class MessageManager;
public:
    MessageSyncResponse();

    const QList<Message> &getMessages() const;
    void setMessages(const QList<Message> &newMessages);

private:
    QList<Message>  messages;
};

