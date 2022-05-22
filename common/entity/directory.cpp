#include "directory.h"

Directory::Directory()
{

}

const QString &Directory::getDirectoryID() const
{
    return directoryID;
}

void Directory::setDirectoryID(const QString &newDirectoryID)
{
    directoryID = newDirectoryID;
}

qint64 Directory::getDirectorySize() const
{
    return directorySize;
}

const QByteArray &Directory::getDirectoryName() const
{
    return directoryName;
}

void Directory::setDirectoryName(const QByteArray &newDirectoryName)
{
    directoryName = newDirectoryName;
}

void Directory::setDirectorySize(qint64 newDirectorySize)
{
    directorySize = newDirectorySize;
}

qint64 Directory::getItemCount() const
{
    return itemCount;
}

void Directory::setItemCount(qint64 newItemCount)
{
    itemCount = newItemCount;
}

const QDateTime &Directory::getCreateDate() const
{
    return createDate;
}

void Directory::setCreateDate(const QDateTime &newCreateDate)
{
    createDate = newCreateDate;
}

const QDateTime &Directory::getAccessDate() const
{
    return accessDate;
}

void Directory::setAccessDate(const QDateTime &newAccessDate)
{
    accessDate = newAccessDate;
}

const QDateTime &Directory::getModifyDate() const
{
    return modifyDate;
}

void Directory::setModifyDate(const QDateTime &newModifyDate)
{
    modifyDate = newModifyDate;
}

const QList<DirectoryItem> &Directory::getItems() const
{
    return items;
}

void Directory::setItems(const QList<DirectoryItem> &newItems)
{
    items = newItems;
}

