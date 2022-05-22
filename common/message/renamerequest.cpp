#include "renamerequest.h"

RenameRequest::RenameRequest()
{

}

qint8 RenameRequest::getType() const
{
    return type;
}

void RenameRequest::setType(qint8 newType)
{
    type = newType;
}

const QString &RenameRequest::getDirectoryID() const
{
    return directoryID;
}

void RenameRequest::setDirectoryID(const QString &newDirectoryID)
{
    directoryID = newDirectoryID;
}

const QString &RenameRequest::getItemID() const
{
    return itemID;
}

void RenameRequest::setItemID(const QString &newItemID)
{
    itemID = newItemID;
}

const QByteArray &RenameRequest::getNewName() const
{
    return newName;
}

void RenameRequest::setNewName(const QByteArray &newNewName)
{
    newName = newNewName;
}
