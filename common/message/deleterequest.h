#ifndef DELETEREQUEST_H
#define DELETEREQUEST_H

#include "requestbase.h"
class MessageManager;
class DeleteRequest : public RequestBase
{
    friend class MessageManager;
public:
    DeleteRequest();

    const QString &getDirectoryID() const;
    void setDirectoryID(const QString &newDirectoryID);
    const QString &getItemID() const;
    void setItemID(const QString &newItemID);

    qint8 getType() const;
    void setType(qint8 newType);

private:
    qint8       type;
    QString     directoryID;
    QString     itemID;

};

#endif // DELETEREQUEST_H
