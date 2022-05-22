#pragma once

#include "common/globalmarco.h"
#include "common/entity/directoryitem.h"

class DirectoryItem{
public:
    DirectoryItem();
    qint8 getItemType() const;
    void setItemType(qint8 newItemType);
    const QString &getItemID() const;
    void setItemID(const QString &newItemID);
    const QDateTime &getCreateDate() const;
    void setCreateDate(const QDateTime &newCreateDate);
    qint64 getItemSize() const;
    void setItemSize(qint64 newItemSize);
    const QByteArray &getItemKey() const;
    void setItemKey(const QByteArray &newItemKey);
    const QByteArray &getItemHash() const;
    void setItemHash(const QByteArray &newItemHash);
    const QByteArray &getItemName() const;
    void setItemName(const QByteArray &newItemName);

private:
    qint8        itemType;
    QString      itemID;
    QByteArray   itemName;
    QDateTime    createDate;
    qint64       itemSize;
    QByteArray   itemKey;
    QByteArray   itemHash;
};

