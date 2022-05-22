#ifndef RENAMEREQUEST_H
#define RENAMEREQUEST_H

#include "requestbase.h"
class MessageManager;
class RenameRequest : public RequestBase{
    friend class MessageManager;
public:
    RenameRequest();
    qint8 getType() const;
    void setType(qint8 newType);
    const QString &getDirectoryID() const;
    void setDirectoryID(const QString &newDirectoryID);
    const QString &getItemID() const;
    void setItemID(const QString &newItemID);


    const QByteArray &getNewName() const;
    void setNewName(const QByteArray &newNewName);

private:
    qint8       type;
    QString     directoryID;
    QString     itemID;
    QByteArray newName;
};

#endif // RENAMEREQUEST_H
