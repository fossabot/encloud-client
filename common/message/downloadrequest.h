#pragma once
#include "common/globalmarco.h"
#include "common/message/requestbase.h"
class MessageManager;
class DownloadRequest : public RequestBase
{
    friend class MessageManager;
public:
    DownloadRequest();

    const QString &getItemID() const;
    void setItemID(const QString &newItemID);

private:
    QString itemID;


};

