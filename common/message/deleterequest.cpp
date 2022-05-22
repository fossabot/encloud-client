#include "deleterequest.h"

DeleteRequest::DeleteRequest()
{

}

const QString &DeleteRequest::getDirectoryID() const
{
    return directoryID;
}

void DeleteRequest::setDirectoryID(const QString &newDirectoryID)
{
    directoryID = newDirectoryID;
}

const QString &DeleteRequest::getItemID() const
{
    return itemID;
}

void DeleteRequest::setItemID(const QString &newItemID)
{
    itemID = newItemID;
}

qint8 DeleteRequest::getType() const
{
    return type;
}

void DeleteRequest::setType(qint8 newType)
{
    type = newType;
}
