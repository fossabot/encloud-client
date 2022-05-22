#include "directoryitem.h"

DirectoryItem::DirectoryItem(){

}

qint8 DirectoryItem::getItemType() const
{
    return itemType;
}

void DirectoryItem::setItemType(qint8 newItemType)
{
    itemType = newItemType;
}

const QString &DirectoryItem::getItemID() const
{
    return itemID;
}

void DirectoryItem::setItemID(const QString &newItemID)
{
    itemID = newItemID;
}


const QDateTime &DirectoryItem::getCreateDate() const
{
    return createDate;
}

void DirectoryItem::setCreateDate(const QDateTime &newCreateDate)
{
    createDate = newCreateDate;
}

qint64 DirectoryItem::getItemSize() const
{
    return itemSize;
}

void DirectoryItem::setItemSize(qint64 newItemSize)
{
    itemSize = newItemSize;
}

const QByteArray &DirectoryItem::getItemKey() const
{
    return itemKey;
}

void DirectoryItem::setItemKey(const QByteArray &newItemKey)
{
    itemKey = newItemKey;
}

const QByteArray &DirectoryItem::getItemHash() const
{
    return itemHash;
}

void DirectoryItem::setItemHash(const QByteArray &newItemHash)
{
    itemHash = newItemHash;
}

const QByteArray &DirectoryItem::getItemName() const
{
    return itemName;
}

void DirectoryItem::setItemName(const QByteArray &newItemName)
{
    itemName = newItemName;
}

